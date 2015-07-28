/*-
********************************************************************************
Copyright (C) 2015 Annapurna Labs Ltd.

This file may be licensed under the terms of the Annapurna Labs Commercial
License Agreement.

Alternatively, this file can be distributed under the terms of the GNU General
Public License V2 as published by the Free Software Foundation and can be
found at http://www.gnu.org/licenses/gpl-2.0.html

Alternatively, redistribution and use in source and binary forms, with or
without modification, are permitted provided that the following conditions are
met:

    *     Redistributions of source code must retain the above copyright notice,
this list of conditions and the following disclaimer.

    *     Redistributions in binary form must reproduce the above copyright
notice, this list of conditions and the following disclaimer in
the documentation and/or other materials provided with the
distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*******************************************************************************/

/**
 * @defgroup group_common HAL Common Layer
 *  @{
 * @file   al_hal_types.h
 *
 * @brief  macros used by HALs and platform layer
 *
 */

#ifndef __AL_HAL_TYPES_H__
#define __AL_HAL_TYPES_H__

#include "al_hal_plat_types.h"
#include "al_hal_plat_services.h"

/* *INDENT-OFF* */
#ifdef __cplusplus
extern "C" {
#endif
/* *INDENT-ON* */

/* Common defines */

#if (!AL_TRUE) || (AL_FALSE)
#error "AL_TRUE must be non zero and AL_FALSE must be zero"
#endif

typedef int AL_RETURN;

#if !defined(NULL)
#define NULL		(void *)0
#endif

#if !defined(likely)
#define likely(x)	(__builtin_expect(!!(x), 1))
#define unlikely(x)	(__builtin_expect(!!(x), 0))
#endif


#ifdef __GNUC__
#if !defined(__packed)
#define __packed __attribute__ ((packed))
#endif
  /* packed and alinged types */
#define __packed_a4 __attribute__ ((packed, aligned(4)))
#define __packed_a8 __attribute__ ((packed, aligned(8)))
#define __packed_a16 __attribute__ ((packed, aligned(16)))

#else
#if !defined(__packed)
#error "__packed is not defined!!"
#endif
#endif

#if !defined(__iomem)
#define __iomem
#endif

#if !defined(__cache_aligned)
#ifdef __GNUC__
#define __cache_aligned __attribute__ ((__aligned__(64)))
#else
#define __cache_aligned
#endif
#endif

#if !defined(INLINE)
#ifdef __GNUC__
#define INLINE inline
#else
#define INLINE
#endif
#endif

/* *INDENT-OFF* */
#ifdef __cplusplus
}
#endif
/* *INDENT-ON* */
/** @} end of Common group */
#endif				/* __TYPES_H__ */
