/*-
 * Copyright (c) 1989, 1990 William F. Jolitz.
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	from: vector.s, 386BSD 0.1 unknown origin
 * $FreeBSD$
 */

/*
 * Interrupt entry points for external interrupts triggered by I/O APICs
 * as well as IPI handlers.
 */

#include "opt_smp.h"

#include <machine/asmacros.h>
#include <machine/specialreg.h>
#include <x86/apicreg.h>

#include "assym.s"

	.text
	SUPERALIGN_TEXT
	/* End Of Interrupt to APIC */
as_lapic_eoi:
	cmpl	$0,x2apic_mode
	jne	1f
	movl	lapic_map,%eax
	movl	$0,LA_EOI(%eax)
	ret
1:
	movl	$MSR_APIC_EOI,%ecx
	xorl	%eax,%eax
	xorl	%edx,%edx
	wrmsr
	ret

/*
 * I/O Interrupt Entry Point.  Rather than having one entry point for
 * each interrupt source, we use one entry point for each 32-bit word
 * in the ISR.  The handler determines the highest bit set in the ISR,
 * translates that into a vector, and passes the vector to the
 * lapic_handle_intr() function.
 */
#define	ISR_VEC(index, vec_name)					\
	.text ;								\
	SUPERALIGN_TEXT ;						\
IDTVEC(vec_name) ;							\
	PUSH_FRAME ;							\
	SET_KERNEL_SREGS ;						\
	cld ;								\
	FAKE_MCOUNT(TF_EIP(%esp)) ;					\
	cmpl	$0,x2apic_mode ;					\
	je	1f ;							\
	movl	$(MSR_APIC_ISR0 + index),%ecx ;				\
	rdmsr ;								\
	jmp	2f ;							\
1: ;									\
	movl	lapic_map, %edx ;/* pointer to local APIC */		\
	movl	LA_ISR + 16 * (index)(%edx), %eax ;	/* load ISR */	\
2: ;									\
	bsrl	%eax, %eax ;	/* index of highest set bit in ISR */	\
	jz	3f ;							\
	addl	$(32 * index),%eax ;					\
	pushl	%esp		;                                       \
	pushl	%eax ;		/* pass the IRQ */			\
	call	lapic_handle_intr ;					\
	addl	$8, %esp ;	/* discard parameter */			\
3: ;									\
	MEXITCOUNT ;							\
	jmp	doreti

/*
 * Handle "spurious INTerrupts".
 * Notes:
 *  This is different than the "spurious INTerrupt" generated by an
 *   8259 PIC for missing INTs.  See the APIC documentation for details.
 *  This routine should NOT do an 'EOI' cycle.
 */
	.text
	SUPERALIGN_TEXT
IDTVEC(spuriousint)

	/* No EOI cycle used here */

	iret

	ISR_VEC(1, apic_isr1)
	ISR_VEC(2, apic_isr2)
	ISR_VEC(3, apic_isr3)
	ISR_VEC(4, apic_isr4)
	ISR_VEC(5, apic_isr5)
	ISR_VEC(6, apic_isr6)
	ISR_VEC(7, apic_isr7)

/*
 * Local APIC periodic timer handler.
 */
	.text
	SUPERALIGN_TEXT
IDTVEC(timerint)
	PUSH_FRAME
	SET_KERNEL_SREGS
	cld
	FAKE_MCOUNT(TF_EIP(%esp))
	pushl	%esp
	call	lapic_handle_timer
	add	$4, %esp
	MEXITCOUNT
	jmp	doreti

/*
 * Local APIC CMCI handler.
 */
	.text
	SUPERALIGN_TEXT
IDTVEC(cmcint)
	PUSH_FRAME
	SET_KERNEL_SREGS
	cld
	FAKE_MCOUNT(TF_EIP(%esp))
	call	lapic_handle_cmc
	MEXITCOUNT
	jmp	doreti

/*
 * Local APIC error interrupt handler.
 */
	.text
	SUPERALIGN_TEXT
IDTVEC(errorint)
	PUSH_FRAME
	SET_KERNEL_SREGS
	cld
	FAKE_MCOUNT(TF_EIP(%esp))
	call	lapic_handle_error
	MEXITCOUNT
	jmp	doreti

#ifdef XENHVM
/*
 * Xen event channel upcall interrupt handler.
 * Only used when the hypervisor supports direct vector callbacks.
 */
	.text
	SUPERALIGN_TEXT
IDTVEC(xen_intr_upcall)
	PUSH_FRAME
	SET_KERNEL_SREGS
	cld
	FAKE_MCOUNT(TF_EIP(%esp))
	pushl	%esp
	call	xen_intr_handle_upcall
	add	$4, %esp
	MEXITCOUNT
	jmp	doreti
#endif

#ifdef SMP
/*
 * Global address space TLB shootdown.
 */
	.text
	SUPERALIGN_TEXT
invltlb_ret:
	call	as_lapic_eoi
	jmp	doreti

	SUPERALIGN_TEXT
IDTVEC(invltlb)
	PUSH_FRAME
	SET_KERNEL_SREGS
	cld

	call	invltlb_handler

	jmp	invltlb_ret

/*
 * Single page TLB shootdown
 */
	.text
	SUPERALIGN_TEXT
IDTVEC(invlpg)
	PUSH_FRAME
	SET_KERNEL_SREGS
	cld

	call	invlpg_handler

	jmp	invltlb_ret

/*
 * Page range TLB shootdown.
 */
	.text
	SUPERALIGN_TEXT
IDTVEC(invlrng)
	PUSH_FRAME
	SET_KERNEL_SREGS
	cld

	call	invlrng_handler

	jmp	invltlb_ret

/*
 * Invalidate cache.
 */
	.text
	SUPERALIGN_TEXT
IDTVEC(invlcache)
	PUSH_FRAME
	SET_KERNEL_SREGS
	cld

	call	invlcache_handler

	jmp	invltlb_ret

/*
 * Handler for IPIs sent via the per-cpu IPI bitmap.
 */
	.text
	SUPERALIGN_TEXT
IDTVEC(ipi_intr_bitmap_handler)	
	PUSH_FRAME
	SET_KERNEL_SREGS
	cld

	call	as_lapic_eoi
	
	FAKE_MCOUNT(TF_EIP(%esp))

	call	ipi_bitmap_handler
	MEXITCOUNT
	jmp	doreti

/*
 * Executed by a CPU when it receives an IPI_STOP from another CPU.
 */
	.text
	SUPERALIGN_TEXT
IDTVEC(cpustop)
	PUSH_FRAME
	SET_KERNEL_SREGS
	cld

	call	as_lapic_eoi
	call	cpustop_handler
	jmp	doreti

/*
 * Executed by a CPU when it receives an IPI_SUSPEND from another CPU.
 */
	.text
	SUPERALIGN_TEXT
IDTVEC(cpususpend)
	PUSH_FRAME
	SET_KERNEL_SREGS
	cld

	call	as_lapic_eoi
	call	cpususpend_handler
	jmp	doreti

/*
 * Executed by a CPU when it receives a RENDEZVOUS IPI from another CPU.
 *
 * - Calls the generic rendezvous action function.
 */
	.text
	SUPERALIGN_TEXT
IDTVEC(rendezvous)
	PUSH_FRAME
	SET_KERNEL_SREGS
	cld

#ifdef COUNT_IPIS
	movl	PCPU(CPUID), %eax
	movl	ipi_rendezvous_counts(,%eax,4), %eax
	incl	(%eax)
#endif
	call	smp_rendezvous_action

	call	as_lapic_eoi
	jmp	doreti
	
#endif /* SMP */
