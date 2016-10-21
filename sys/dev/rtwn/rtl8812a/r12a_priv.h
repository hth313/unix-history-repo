/*-
 * Copyright (c) 2016 Andriy Voskoboinyk <avos@FreeBSD.org>
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
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * $FreeBSD$
 */

#ifndef R12A_PRIV_H
#define R12A_PRIV_H

/*
 * MAC initialization values.
 */
#define RTL8812AU_MAC_PROG_START \
	{ 0x010, 0x0c },

#define RTL8812AU_MAC_PROG_END \
	{ 0x025, 0x0f }, { 0x072, 0x00 }, { 0x420, 0x80 }, { 0x428, 0x0a }, \
	{ 0x429, 0x10 }, { 0x430, 0x00 }, { 0x431, 0x00 }, { 0x432, 0x00 }, \
	{ 0x433, 0x01 }, { 0x434, 0x04 }, { 0x435, 0x05 }, { 0x436, 0x07 }, \
	{ 0x437, 0x08 }, { 0x43c, 0x04 }, { 0x43d, 0x05 }, { 0x43e, 0x07 }, \
	{ 0x43f, 0x08 }, { 0x440, 0x5d }, { 0x441, 0x01 }, { 0x442, 0x00 }, \
	{ 0x444, 0x10 }, { 0x445, 0x00 }, { 0x446, 0x00 }, { 0x447, 0x00 }, \
	{ 0x448, 0x00 }, { 0x449, 0xf0 }, { 0x44a, 0x0f }, { 0x44b, 0x3e }, \
	{ 0x44c, 0x10 }, { 0x44d, 0x00 }, { 0x44e, 0x00 }, { 0x44f, 0x00 }, \
	{ 0x450, 0x00 }, { 0x451, 0xf0 }, { 0x452, 0x0f }, { 0x453, 0x00 }, \
	{ 0x45b, 0x80 }, { 0x460, 0x66 }, { 0x461, 0x66 }, { 0x4c8, 0xff }, \
	{ 0x4c9, 0x08 }, { 0x4cc, 0xff }, { 0x4cd, 0xff }, { 0x4ce, 0x01 }, \
	{ 0x500, 0x26 }, { 0x501, 0xa2 }, { 0x502, 0x2f }, { 0x503, 0x00 }, \
	{ 0x504, 0x28 }, { 0x505, 0xa3 }, { 0x506, 0x5e }, { 0x507, 0x00 }, \
	{ 0x508, 0x2b }, { 0x509, 0xa4 }, { 0x50a, 0x5e }, { 0x50b, 0x00 }, \
	{ 0x50c, 0x4f }, { 0x50d, 0xa4 }, { 0x50e, 0x00 }, { 0x50f, 0x00 }, \
	{ 0x512, 0x1c }, { 0x514, 0x0a }, { 0x516, 0x0a }, { 0x525, 0x4f }, \
	{ 0x550, 0x10 }, { 0x551, 0x10 }, { 0x559, 0x02 }, { 0x55c, 0x50 }, \
	{ 0x55d, 0xff }, { 0x604, 0x09 }, { 0x605, 0x30 }, { 0x607, 0x03 }, \
	{ 0x608, 0x0e }, { 0x609, 0x2a }, { 0x620, 0xff }, { 0x621, 0xff }, \
	{ 0x622, 0xff }, { 0x623, 0xff }, { 0x624, 0xff }, { 0x625, 0xff }, \
	{ 0x626, 0xff }, { 0x627, 0xff }, { 0x638, 0x50 }, { 0x63c, 0x0a }, \
	{ 0x63d, 0x0a }, { 0x63e, 0x0e }, { 0x63f, 0x0e }, { 0x640, 0x80 }, \
	{ 0x642, 0x40 }, { 0x643, 0x00 }, { 0x652, 0xc8 }, { 0x66e, 0x05 }, \
	{ 0x700, 0x21 }, { 0x701, 0x43 }, { 0x702, 0x65 }, { 0x703, 0x87 }, \
	{ 0x708, 0x21 }, { 0x709, 0x43 }, { 0x70a, 0x65 }, { 0x70b, 0x87 }, \
	{ 0x718, 0x40 }

static const struct rtwn_mac_prog rtl8812au_mac_no_ext_pa_lna[] = {
	RTL8812AU_MAC_PROG_START
	{ 0x11, 0x66 },
	RTL8812AU_MAC_PROG_END
}, rtl8812au_mac[] = {
	RTL8812AU_MAC_PROG_START
	{ 0x11, 0x5a },
	RTL8812AU_MAC_PROG_END
};


/*
 * Baseband initialization values.
 */
#define R12A_COND_GPA		0x01
#define R12A_COND_APA		0x02
#define R12A_COND_GLNA		0x04
#define R12A_COND_ALNA		0x08
#define R12A_COND_TYPE(t)	((t) << 4)

static const uint16_t rtl8812au_bb_regs0[] = {
	0x800, 0x804, 0x808, 0x80c, 0x810, 0x814, 0x818, 0x820, 0x824,
	0x828, 0x82c, 0x830, 0x834, 0x838, 0x83c, 0x840, 0x844, 0x848,
	0x84c, 0x850, 0x854, 0x858, 0x85c, 0x860, 0x864, 0x868, 0x86c,
	0x870, 0x874, 0x878, 0x87c, 0x8a0, 0x8a4, 0x8a8, 0x8ac, 0x8b0,
	0x8b4, 0x8b8, 0x8bc, 0x8c0, 0x8c4, 0x8c8, 0x8cc, 0x8d0, 0x8dc,
	0x8d4, 0x8d8, 0x8f8, 0x8fc, 0x900, 0x90c, 0x910, 0x914, 0x918,
	0x91c, 0x920, 0x924, 0x928, 0x92c, 0x930, 0x934, 0x960, 0x964,
	0x968, 0x96c, 0x970, 0x978, 0x97c, 0x980, 0x984, 0x988, 0x990,
	0x994, 0x998, 0x99c, 0x9a0, 0x9a4, 0x9a8, 0x9ac, 0x9b0, 0x9b4,
	0x9b8, 0x9bc, 0x9d0, 0x9d4, 0x9d8, 0x9dc, 0x9e4, 0x9e8, 0xa00,
	0xa04, 0xa08, 0xa0c, 0xa10, 0xa14, 0xa18, 0xa1c, 0xa20, 0xa24,
	0xa28, 0xa2c, 0xa70, 0xa74, 0xa78, 0xa7c, 0xa80, 0xa84, 0xb00,
	0xb04, 0xb08, 0xb0c, 0xb10, 0xb14, 0xb18, 0xb1c, 0xb20, 0xb24,
	0xb28, 0xb2c, 0xb30, 0xb34, 0xb38, 0xb3c, 0xb40, 0xb44, 0xb48,
	0xb4c, 0xb50, 0xb54, 0xb58, 0xb5c, 0xc00, 0xc04, 0xc08, 0xc0c,
	0xc10, 0xc14, 0xc1c, 0xc20, 0xc24, 0xc28, 0xc2c, 0xc30, 0xc34,
	0xc38, 0xc3c, 0xc40, 0xc44, 0xc48, 0xc4c, 0xc50, 0xc54, 0xc58,
	0xc5c, 0xc60, 0xc64
}, rtl8812au_bb_regs1[] = {
	0xc68
}, rtl8812au_bb_regs2[] = {
	0xc6c, 0xc70, 0xc74, 0xc78, 0xc7c, 0xc80, 0xc84, 0xc94, 0xc98,
	0xc9c, 0xca0, 0xca4, 0xca8, 0xcb0, 0xcb4, 0xcb8, 0xe00, 0xe04,
	0xe08, 0xe0c, 0xe10, 0xe14, 0xe1c, 0xe20, 0xe24, 0xe28, 0xe2c,
	0xe30, 0xe34, 0xe38, 0xe3c, 0xe40, 0xe44, 0xe48, 0xe4c, 0xe50,
	0xe54, 0xe58, 0xe5c, 0xe60, 0xe64, 0xe68, 0xe6c, 0xe70, 0xe74,
	0xe78, 0xe7c, 0xe80, 0xe84, 0xe94, 0xe98, 0xe9c, 0xea0, 0xea4,
	0xea8, 0xeb0, 0xeb4, 0xeb8
};

static const uint32_t rtl8812au_bb_vals0[] = {
	0x8020d010, 0x080112e0, 0x0e028233, 0x12131113, 0x20101263,
	0x020c3d10, 0x03a00385, 0x00000000, 0x00030fe0, 0x00000000,
	0x002083dd, 0x2eaaeeb8, 0x0037a706, 0x06c89b44, 0x0000095b,
	0xc0000001, 0x40003cde, 0x6210ff8b, 0x6cfdffb8, 0x28874706,
	0x0001520c, 0x8060e000, 0x74210168, 0x6929c321, 0x79727432,
	0x8ca7a314, 0x338c2878, 0x03333333, 0x31602c2e, 0x00003152,
	0x000fc000, 0x00000013, 0x7f7f7f7f, 0xa202033e, 0x0ff0fa0a,
	0x00000600, 0x000fc080, 0x6c0057ff, 0x4ca520a3, 0x27f00020,
	0x00000000, 0x00012d69, 0x08248492, 0x0000b800, 0x00000000,
	0x940008a0, 0x290b5612, 0x400002c0, 0x00000000, 0x00000701,
	0x00000000, 0x0000fc00, 0x00000404, 0x1c1028c0, 0x64b11a1c,
	0xe0767233, 0x055aa500, 0x00000004, 0xfffe0000, 0xfffffffe,
	0x001fffff, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x801fffff, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x27100000, 0xffff0100, 0xffffff5c, 0xffffffff,
	0x000000ff, 0x00080080, 0x00000000, 0x00000000, 0x81081008,
	0x00000000, 0x01081008, 0x01081008, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000003, 0x000002d5, 0x00d047c8,
	0x01ff000c, 0x8c838300, 0x2e7f000f, 0x9500bb78, 0x11144028,
	0x00881117, 0x89140f00, 0x1a1b0000, 0x090e1217, 0x00000305,
	0x00900000, 0x101fff00, 0x00000008, 0x00000900, 0x225b0606,
	0x218075b2, 0x001f8c80, 0x03100000, 0x0000b000, 0xae0201eb,
	0x01003207, 0x00009807, 0x01000000, 0x00000002, 0x00000002,
	0x0000001f, 0x03020100, 0x07060504, 0x0b0a0908, 0x0f0e0d0c,
	0x13121110, 0x17161514, 0x0000003a, 0x00000000, 0x00000000,
	0x13000032, 0x48080000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000007, 0x00042020, 0x80410231, 0x00000000,
	0x00000100, 0x01000000, 0x40000003, 0x12121212, 0x12121212,
	0x12121212, 0x12121212, 0x12121212, 0x12121212, 0x12121212,
	0x12121212, 0x12121212, 0x12121212, 0x12121212, 0x12121212,
	0x00000020, 0x0008121c, 0x30000c1c, 0x00000058, 0x34344443,
	0x07003333
}, rtl8812au_bb_vals1_ext_pa_lna[] = {
	0x59791979
}, rtl8812au_bb_vals1[] = {
	0x59799979
}, rtl8812au_bb_vals2[] = {
	0x59795979, 0x19795979, 0x19795979, 0x19791979, 0x19791979,
	0x19791979, 0x19791979, 0x0100005c, 0x00000000, 0x00000000,
	0x00000029, 0x08040201, 0x80402010, 0x77547777, 0x00000077,
	0x00508242, 0x00000007, 0x00042020, 0x80410231, 0x00000000,
	0x00000100, 0x01000000, 0x40000003, 0x12121212, 0x12121212,
	0x12121212, 0x12121212, 0x12121212, 0x12121212, 0x12121212,
	0x12121212, 0x12121212, 0x12121212, 0x12121212, 0x12121212,
	0x00000020, 0x0008121c, 0x30000c1c, 0x00000058, 0x34344443,
	0x07003333, 0x59791979, 0x59795979, 0x19795979, 0x19795979,
	0x19791979, 0x19791979, 0x19791979, 0x19791979, 0x0100005c,
	0x00000000, 0x00000000, 0x00000029, 0x08040201, 0x80402010,
	0x77547777, 0x00000077, 0x00508242
};

static const struct rtwn_bb_prog rtl8812au_bb[] = {
	{
		nitems(rtl8812au_bb_regs0),
		rtl8812au_bb_regs0,
		rtl8812au_bb_vals0,
		{ 0 },
		NULL
	},
	/*
	 * Devices with:
	 * * External 2GHz PA, type 0;
	 * * External 5GHz PA, type 0 or 5;
	 * * External 2GHz LNA, type 0 or 5;
	 * * External 5GHz LNA, type 0;
	 */
	{
		nitems(rtl8812au_bb_regs1),
		rtl8812au_bb_regs1,
		rtl8812au_bb_vals1_ext_pa_lna,
		{
			R12A_COND_GPA | R12A_COND_GLNA |
			R12A_COND_APA | R12A_COND_ALNA |
			R12A_COND_TYPE(0x0),
			R12A_COND_APA | R12A_COND_GLNA |
			R12A_COND_TYPE(0x5), 0
		},
		/*
		 * Others.
		 */
		&(const struct rtwn_bb_prog){
			nitems(rtl8812au_bb_regs1),
			rtl8812au_bb_regs1,
			rtl8812au_bb_vals1,
			{ 0 },
			NULL
		}
	},
	{
		nitems(rtl8812au_bb_regs2),
		rtl8812au_bb_regs2,
		rtl8812au_bb_vals2,
		{ 0 },
		NULL
	}
};


static const uint32_t rtl8812au_agc_vals0_lna_g0[] = {
	0xfc000001, 0xfb020001, 0xfa040001, 0xf9060001, 0xf8080001,
	0xf70a0001, 0xf60c0001, 0xf50e0001, 0xf4100001, 0xf3120001,
	0xf2140001, 0xf1160001, 0xf0180001, 0xef1a0001, 0xee1c0001,
	0xed1e0001, 0xec200001, 0xeb220001, 0xea240001, 0xcd260001,
	0xcc280001, 0xcb2a0001, 0xca2c0001, 0xc92e0001, 0xc8300001,
	0xa6320001, 0xa5340001, 0xa4360001, 0xa3380001, 0xa23a0001,
	0x883c0001, 0x873e0001, 0x86400001, 0x85420001, 0x84440001,
	0x83460001, 0x82480001, 0x814a0001, 0x484c0001, 0x474e0001,
	0x46500001, 0x45520001, 0x44540001, 0x43560001, 0x42580001,
	0x415a0001, 0x255c0001, 0x245e0001, 0x23600001, 0x22620001,
	0x21640001, 0x21660001, 0x21680001, 0x216a0001, 0x216c0001,
	0x216e0001, 0x21700001, 0x21720001, 0x21740001, 0x21760001,
	0x21780001, 0x217a0001, 0x217c0001, 0x217e0001
}, rtl8812au_agc_vals0_lna_g5[] = {
	0xf9000001, 0xf8020001, 0xf7040001, 0xf6060001, 0xf5080001,
	0xf40a0001, 0xf30c0001, 0xf20e0001, 0xf1100001, 0xf0120001,
	0xef140001, 0xee160001, 0xed180001, 0xec1a0001, 0xeb1c0001,
	0xea1e0001, 0xcd200001, 0xcc220001, 0xcb240001, 0xca260001,
	0xc9280001, 0xc82a0001, 0xc72c0001, 0xc62e0001, 0xa5300001,
	0xa4320001, 0xa3340001, 0xa2360001, 0x88380001, 0x873a0001,
	0x863c0001, 0x853e0001, 0x84400001, 0x83420001, 0x82440001,
	0x81460001, 0x48480001, 0x474a0001, 0x464c0001, 0x454e0001,
	0x44500001, 0x43520001, 0x42540001, 0x41560001, 0x25580001,
	0x245a0001, 0x235c0001, 0x225e0001, 0x21600001, 0x21620001,
	0x21640001, 0x21660001, 0x21680001, 0x216a0001, 0x236c0001,
	0x226e0001, 0x21700001, 0x21720001, 0x21740001, 0x21760001,
	0x21780001, 0x217a0001, 0x217c0001, 0x217e0001
}, rtl8812au_agc_vals0[] = {
	0xff000001, 0xff020001, 0xff040001, 0xff060001, 0xff080001,
	0xfe0a0001, 0xfd0c0001, 0xfc0e0001, 0xfb100001, 0xfa120001,
	0xf9140001, 0xf8160001, 0xf7180001, 0xf61a0001, 0xf51c0001,
	0xf41e0001, 0xf3200001, 0xf2220001, 0xf1240001, 0xf0260001,
	0xef280001, 0xee2a0001, 0xed2c0001, 0xec2e0001, 0xeb300001,
	0xea320001, 0xe9340001, 0xe8360001, 0xe7380001, 0xe63a0001,
	0xe53c0001, 0xc73e0001, 0xc6400001, 0xc5420001, 0xc4440001,
	0xc3460001, 0xc2480001, 0xc14a0001, 0xa74c0001, 0xa64e0001,
	0xa5500001, 0xa4520001, 0xa3540001, 0xa2560001, 0xa1580001,
	0x675a0001, 0x665c0001, 0x655e0001, 0x64600001, 0x63620001,
	0x48640001, 0x47660001, 0x46680001, 0x456a0001, 0x446c0001,
	0x436e0001, 0x42700001, 0x41720001, 0x41740001, 0x41760001,
	0x41780001, 0x417a0001, 0x417c0001, 0x417e0001
}, rtl8812au_agc_vals1_lna_a0[] = {
	0xfc800001, 0xfb820001, 0xfa840001, 0xf9860001, 0xf8880001,
	0xf78a0001, 0xf68c0001, 0xf58e0001, 0xf4900001, 0xf3920001,
	0xf2940001, 0xf1960001, 0xf0980001, 0xef9a0001, 0xee9c0001,
	0xed9e0001, 0xeca00001, 0xeba20001, 0xeaa40001, 0xe9a60001,
	0xe8a80001, 0xe7aa0001, 0xe6ac0001, 0xe5ae0001, 0xe4b00001,
	0xe3b20001, 0xa8b40001, 0xa7b60001, 0xa6b80001, 0xa5ba0001,
	0xa4bc0001, 0xa3be0001, 0xa2c00001, 0xa1c20001, 0x68c40001,
	0x67c60001, 0x66c80001, 0x65ca0001, 0x64cc0001, 0x47ce0001,
	0x46d00001, 0x45d20001, 0x44d40001, 0x43d60001, 0x42d80001,
	0x08da0001, 0x07dc0001, 0x06de0001, 0x05e00001, 0x04e20001,
	0x03e40001, 0x02e60001, 0x01e80001, 0x01ea0001, 0x01ec0001,
	0x01ee0001, 0x01f00001, 0x01f20001, 0x01f40001, 0x01f60001,
	0x01f80001, 0x01fa0001, 0x01fc0001, 0x01fe0001
}, rtl8812au_agc_vals1[] = {
	0xff800001, 0xff820001, 0xff840001, 0xfe860001, 0xfd880001,
	0xfc8a0001, 0xfb8c0001, 0xfa8e0001, 0xf9900001, 0xf8920001,
	0xf7940001, 0xf6960001, 0xf5980001, 0xf49a0001, 0xf39c0001,
	0xf29e0001, 0xf1a00001, 0xf0a20001, 0xefa40001, 0xeea60001,
	0xeda80001, 0xecaa0001, 0xebac0001, 0xeaae0001, 0xe9b00001,
	0xe8b20001, 0xe7b40001, 0xe6b60001, 0xe5b80001, 0xe4ba0001,
	0xe3bc0001, 0xa8be0001, 0xa7c00001, 0xa6c20001, 0xa5c40001,
	0xa4c60001, 0xa3c80001, 0xa2ca0001, 0xa1cc0001, 0x68ce0001,
	0x67d00001, 0x66d20001, 0x65d40001, 0x64d60001, 0x47d80001,
	0x46da0001, 0x45dc0001, 0x44de0001, 0x43e00001, 0x42e20001,
	0x08e40001, 0x07e60001, 0x06e80001, 0x05ea0001, 0x04ec0001,
	0x03ee0001, 0x02f00001, 0x01f20001, 0x01f40001, 0x01f60001,
	0x01f80001, 0x01fa0001, 0x01fc0001, 0x01fe0001
};

static const struct rtwn_agc_prog rtl8812au_agc[] = {
	/*
	 * External 2GHz LNA (type 0).
	 */
	{
		nitems(rtl8812au_agc_vals0_lna_g0),
		rtl8812au_agc_vals0_lna_g0,
		{ R12A_COND_GLNA | R12A_COND_TYPE(0x0), 0 },
		/*
		 * External 2GHz LNA (type 5).
		 */
		&(const struct rtwn_agc_prog){
			nitems(rtl8812au_agc_vals0_lna_g5),
			rtl8812au_agc_vals0_lna_g5,
			{ R12A_COND_GLNA | R12A_COND_TYPE(0x5), 0 },
			/*
			 * Others.
			 */
			&(const struct rtwn_agc_prog){
				nitems(rtl8812au_agc_vals0),
				rtl8812au_agc_vals0,
				{ 0 },
				NULL
			}
		}
	},
	/*
	 * External 5GHz LNA (type 0).
	 */
	{
		nitems(rtl8812au_agc_vals1_lna_a0),
		rtl8812au_agc_vals1_lna_a0,
		{ R12A_COND_ALNA | R12A_COND_TYPE(0x0), 0 },
		/*
		 * Others.
		 */
		&(const struct rtwn_agc_prog){
			nitems(rtl8812au_agc_vals1),
			rtl8812au_agc_vals1,
			{ 0 },
			NULL
		}
	}
};

/*
 * RF initialization values.
 */
static const uint8_t rtl8812au_rf0_regs0[] = {
	0x00, 0x18, 0x56, 0x66, 0x1e, 0x89
}, rtl8812au_rf0_regs1[] = {
	0x86
}, rtl8812au_rf0_regs2[] = {
	0x8b
}, rtl8812au_rf0_regs3[] = {
	0xb1, 0xb3, 0xb4, 0xba,	0x18, 0xef
}, rtl8812au_rf0_regs4[] = {
	0x3b, 0x3b, 0x3b, 0x3b, 0x3b, 0x3b, 0x3b
}, rtl8812au_rf0_regs5[] = {
	0xef, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34,
	0x34
}, rtl8812au_rf0_regs6[] = {
	0xef, 0xef, 0xdf, 0x35, 0x35, 0x35, 0x36, 0x36, 0x36, 0x36, 0xef,
	0x51, 0x52, 0x53, 0x54, 0xef, 0x08, 0x18, 0xef, 0x3a, 0x3b, 0x3c,
	0x3a, 0x3b, 0x3c, 0x3a, 0x3b, 0x3c, 0x3a, 0x3b, 0x3c, 0x3a, 0x3b,
	0x3c, 0x3a, 0x3b, 0x3c, 0x3a, 0x3b, 0x3c, 0x3a, 0x3b, 0x3c, 0x3a,
	0x3b, 0x3c, 0x3a, 0x3b, 0x3c, 0x3a, 0x3b, 0x3c, 0x3a, 0x3b, 0x3c,
	0x3a, 0x3b, 0x3c, 0x3a, 0x3b, 0x3c, 0x3a, 0x3b, 0x3c, 0x3a, 0x3b,
	0x3c, 0x3a, 0x3b, 0x3c, 0x3a, 0x3b, 0x3c, 0x3a, 0x3b, 0x3c, 0x3a,
	0x3b, 0x3c, 0x3a, 0x3b, 0x3c, 0x3a, 0x3b, 0x3c, 0x3a, 0x3b, 0x3c,
	0x3a, 0x3b, 0x3c, 0xef
}, rtl8812au_rf0_regs7[] = {
	0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34,
	0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34,
	0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34
}, rtl8812au_rf0_regs8[] = {
	0xef, 0x18, 0xef, 0x35, 0x35, 0x35, 0x35, 0x35, 0x35, 0x35, 0x35,
	0x35, 0xef, 0x18, 0xef, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36,
	0x36, 0x36, 0x36, 0x36, 0x36, 0xef, 0xef, 0x3c, 0x3c, 0x3c,
}, rtl8812au_rf0_regs9[] = {
	0xef, 0x18, 0xef, 0xdf, 0x1f
}, rtl8812au_rf0_regs10[] = {
	0x61, 0x62, 0x63, 0x64, 0x65
}, rtl8812au_rf0_regs11[] = {
	0x08, 0x1c, 0xb4, 0x18, 0xfe, 0xfe, 0xfe, 0xfe, 0xb4, 0x18
}, rtl8812au_rf1_regs0[] = {
	0x56, 0x66, 0x89
}, rtl8812au_rf1_regs3[] = {
	0xb1, 0xb3, 0xb4, 0xba, 0x18, 0xef
};

static const uint32_t rtl8812au_rf0_vals0[] = {
	0x10000, 0x1712a, 0x51cf2, 0x40000, 0x80000, 0x00080
}, rtl8812au_rf0_vals1_lna_g0_g5[] = {
	0x14b3a
}, rtl8812au_rf0_vals1[] = {
	0x14b38
}, rtl8812au_rf0_vals2_lna_a0[] = {
	0x80180
}, rtl8812au_rf0_vals2[] = {
	0x87180
}, rtl8812au_rf0_vals3[] = {
	0x1fc1a, 0xf0810, 0x1a78d, 0x86180, 0x00006, 0x02000
}, rtl8812au_rf0_vals4_lna_g0_g5[] = {
	0x3f218, 0x30a58, 0x2fa58, 0x22590, 0x1fa50, 0x10248, 0x08240
}, rtl8812au_rf0_vals4[] = {
	0x38a58, 0x37a58, 0x2a590, 0x27a50, 0x18248, 0x10240, 0x08240
}, rtl8812au_rf0_vals5_pa_g0[] = {
	0x00100, 0x0a4ee, 0x09076, 0x08073, 0x07070, 0x0606d, 0x0506a,
	0x04049, 0x03046, 0x02028, 0x01025, 0x00022
}, rtl8812au_rf0_vals5[] = {
	0x00100, 0x0adf4, 0x09df1, 0x08dee, 0x07deb, 0x06de8, 0x05de5,
	0x04de2, 0x03ce6, 0x024e7, 0x014e4, 0x004e1
}, rtl8812au_rf0_vals6[] = {
	0x00000, 0x020a2, 0x00080, 0x00192, 0x08192, 0x10192, 0x00024,
	0x08024, 0x10024, 0x18024, 0x00000, 0x00c21, 0x006d9, 0xfc649,
	0x0017e, 0x00002, 0x08400, 0x1712a, 0x01000, 0x00080, 0x3a02c,
	0x04000, 0x00400, 0x3202c, 0x10000, 0x000a0, 0x2b064, 0x04000,
	0x000d8, 0x23070, 0x04000, 0x00468, 0x1b870, 0x10000, 0x00098,
	0x12085, 0xe4000, 0x00418, 0x0a080, 0xf0000, 0x00418, 0x02080,
	0x10000, 0x00080, 0x7a02c, 0x04000, 0x00400, 0x7202c, 0x10000,
	0x000a0, 0x6b064, 0x04000, 0x000d8, 0x63070, 0x04000, 0x00468,
	0x5b870, 0x10000, 0x00098, 0x52085, 0xe4000, 0x00418, 0x4a080,
	0xf0000, 0x00418, 0x42080, 0x10000, 0x00080, 0xba02c, 0x04000,
	0x00400, 0xb202c, 0x10000, 0x000a0, 0xab064, 0x04000, 0x000d8,
	0xa3070, 0x04000, 0x00468, 0x9b870, 0x10000, 0x00098, 0x92085,
	0xe4000, 0x00418, 0x8a080, 0xf0000, 0x00418, 0x82080, 0x10000,
	0x01100
}, rtl8812au_rf0_vals7_pa_a0[] = {
	0x4a0b2, 0x490af, 0x48070, 0x4706d, 0x46050, 0x4504d, 0x4404a,
	0x43047, 0x4200a, 0x41007, 0x40004, 0x2a0b2, 0x290af, 0x28070,
	0x2706d, 0x26050, 0x2504d, 0x2404a, 0x23047, 0x2200a, 0x21007,
	0x20004, 0x0a0b2, 0x090af, 0x08070, 0x0706d, 0x06050, 0x0504d,
	0x0404a, 0x03047, 0x0200a, 0x01007, 0x00004
}, rtl8812au_rf0_vals7_pa_a5[] = {
	0x4a0b2, 0x490af, 0x48070, 0x4706d, 0x4604d, 0x4504a, 0x44047,
	0x43044, 0x42007, 0x41004, 0x40001, 0x2a0b4, 0x290b1, 0x28072,
	0x2706f, 0x2604f, 0x2504c, 0x24049, 0x23046, 0x22009, 0x21006,
	0x20003, 0x0a0b2, 0x090af, 0x08070, 0x0706d, 0x0604d, 0x0504a,
	0x04047, 0x03044, 0x02007, 0x01004, 0x00001
}, rtl8812au_rf0_vals7[] = {
	0x4adf5, 0x49df2, 0x48def, 0x47dec, 0x46de9, 0x45de6, 0x44de3,
	0x438c8, 0x428c5, 0x418c2, 0x408c0, 0x2adf5, 0x29df2, 0x28def,
	0x27dec, 0x26de9, 0x25de6, 0x24de3, 0x238c8, 0x228c5, 0x218c2,
	0x208c0, 0x0aff7, 0x09df7, 0x08df4, 0x07df1, 0x06dee, 0x05deb,
	0x04de8, 0x038cc, 0x028c9, 0x018c6, 0x008c3
}, rtl8812au_rf0_vals8_pa_a0_a5[] = {
	0x00000, 0x1712a, 0x00040, 0x001d4, 0x081d4, 0x101d4, 0x201b4,
	0x281b4, 0x301b4, 0x401b4, 0x481b4, 0x501b4, 0x00000, 0x1712a,
	0x00010, 0x04bfb, 0x0cbfb, 0x14bfb, 0x1cbfb, 0x24f4b, 0x2cf4b,
	0x34f4b, 0x3cf4b, 0x44f4b, 0x4cf4b, 0x54f4b, 0x5cf4b, 0x00000,
	0x00008, 0x002cc, 0x00522, 0x00902
}, rtl8812au_rf0_vals8[] = {
	0x00000, 0x1712a, 0x00040, 0x00188, 0x08147, 0x10147, 0x201d7,
	0x281d7, 0x301d7, 0x401d8, 0x481d8, 0x501d8, 0x00000, 0x1712a,
	0x00010, 0x84eb4, 0x8cc35, 0x94c35, 0x9cc35, 0xa4c35, 0xacc35,
	0xb4c35, 0xbcc35, 0xc4c34, 0xccc35, 0xd4c35, 0xdcc35, 0x00000,
	0x00008, 0x002a8, 0x005a2, 0x00880
}, rtl8812au_rf0_vals9[] = {
	0x00000, 0x1712a, 0x00002, 0x00080, 0x00064
}, rtl8812au_rf0_vals10_pa_a0[] = {
	0xfdd43, 0x38f4b, 0x32117, 0x194ac, 0x931d1
}, rtl8812au_rf0_vals10_pa_a5[] = {
	0xfdd43, 0x38f4b, 0x32117, 0x194ac, 0x931d2
}, rtl8812au_rf0_vals10[] = {
	0xe5d53, 0x38fcd, 0x114eb, 0x196ac, 0x911d7
}, rtl8812au_rf0_vals11[] = {
	0x08400, 0x739d2, 0x1e78d, 0x1f12a, 0x0c350, 0x0c350, 0x0c350,
	0x0c350, 0x1a78d, 0x1712a
}, rtl8812au_rf1_vals0[] = {
	0x51cf2, 0x40000, 0x00080
}, rtl8812au_rf1_vals3[] = {
	0x1fc1a, 0xf0810, 0x1a78d, 0x86180, 0x00006, 0x02000
}, rtl8812au_rf1_vals6[] = {
	0x00000, 0x020a2, 0x00080, 0x00192, 0x08192, 0x10192, 0x00024,
	0x08024, 0x10024, 0x18024, 0x00000, 0x00c21, 0x006d9, 0xfc649,
	0x0017e, 0x00002, 0x08400, 0x1712a, 0x01000, 0x00080, 0x3a02c,
	0x04000, 0x00400, 0x3202c, 0x10000, 0x000a0, 0x2b064, 0x04000,
	0x000d8, 0x23070, 0x04000, 0x00468, 0x1b870, 0x10000, 0x00098,
	0x12085, 0xe4000, 0x00418, 0x0a080, 0xf0000, 0x00418, 0x02080,
	0x10000, 0x00080, 0x7a02c, 0x04000, 0x00400, 0x7202c, 0x10000,
	0x000a0, 0x6b064, 0x04000, 0x000d8, 0x63070, 0x04000, 0x00468,
	0x5b870, 0x10000, 0x00098, 0x52085, 0xe4000, 0x00418, 0x4a080,
	0xf0000, 0x00418, 0x42080, 0x10000, 0x00080, 0xba02c, 0x04000,
	0x00400, 0xb202c, 0x10000, 0x000a0, 0xab064, 0x04000, 0x000d8,
	0xa3070, 0x04000, 0x00468, 0x9b870, 0x10000, 0x00098, 0x92085,
	0xe4000, 0x00418, 0x8a080, 0xf0000, 0x00418, 0x82080, 0x10000,
	0x01100
}, rtl8812au_rf1_vals7_pa_a5[] = {
	0x4a0b1, 0x490ae, 0x4806f, 0x4706c, 0x4604c, 0x45049, 0x44046,
	0x43043, 0x42006, 0x41003, 0x40000, 0x2a0b3, 0x290b0, 0x28071,
	0x2706e, 0x2604e, 0x2504b, 0x24048, 0x23045, 0x22008, 0x21005,
	0x20002, 0x0a0b3, 0x090b0, 0x08070, 0x0706d, 0x0604d, 0x0504a,
	0x04047, 0x03044, 0x02007, 0x01004, 0x00001
}, rtl8812au_rf1_vals8_pa_a0_a5[] = {
	0x00000, 0x1712a, 0x00040, 0x001c5, 0x081c5, 0x101c5, 0x20174,
	0x28174, 0x30174, 0x40185, 0x48185, 0x50185, 0x00000, 0x1712a,
	0x00010, 0x05b8b, 0x0db8b, 0x15b8b, 0x1db8b, 0x262db, 0x2e2db,
	0x362db, 0x3e2db, 0x4553b, 0x4d53b, 0x5553b, 0x5d53b, 0x00000,
	0x00008, 0x002dc, 0x00524, 0x00902
}, rtl8812au_rf1_vals10_pa_g0_a0[] = {
	0xeac43, 0x38f47, 0x31157, 0x1c4ac, 0x931d1
}, rtl8812au_rf1_vals10_pa_a5[] = {
	0xeac43, 0x38f47, 0x31157, 0x1c4ac, 0x931d2
};

static const struct rtwn_rf_prog rtl8812au_rf[] = {
	/* RF chain 0. */
	{
		nitems(rtl8812au_rf0_regs0),
		rtl8812au_rf0_regs0,
		rtl8812au_rf0_vals0,
		{ 0 },
		NULL
	},
	/* External 2GHz LNA, type 0 or 5. */
	{
		nitems(rtl8812au_rf0_regs1),
		rtl8812au_rf0_regs1,
		rtl8812au_rf0_vals1_lna_g0_g5,
		{
			R12A_COND_GLNA | R12A_COND_TYPE(0x0),
			R12A_COND_GLNA | R12A_COND_TYPE(0x5), 0
		},
		/* Others. */
		&(const struct rtwn_rf_prog){
			nitems(rtl8812au_rf0_regs1),
			rtl8812au_rf0_regs1,
			rtl8812au_rf0_vals1,
			{ 0 },
			NULL
		}
	},
	/* External 5GHz LNA, type 0. */
	{
		nitems(rtl8812au_rf0_regs2),
		rtl8812au_rf0_regs2,
		rtl8812au_rf0_vals2_lna_a0,
		{ R12A_COND_ALNA | R12A_COND_TYPE(0x0), 0 },
		/* Others. */
		&(const struct rtwn_rf_prog){
			nitems(rtl8812au_rf0_regs2),
			rtl8812au_rf0_regs2,
			rtl8812au_rf0_vals2,
			{ 0 },
			NULL
		}
	},
	{
		nitems(rtl8812au_rf0_regs3),
		rtl8812au_rf0_regs3,
		rtl8812au_rf0_vals3,
		{ 0 },
		NULL
	},
	/* External 2GHz LNA, type 0 or 5. */
	{
		nitems(rtl8812au_rf0_regs4),
		rtl8812au_rf0_regs4,
		rtl8812au_rf0_vals4_lna_g0_g5,
		{
			R12A_COND_GLNA | R12A_COND_TYPE(0x0),
			R12A_COND_GLNA | R12A_COND_TYPE(0x5), 0
		},
		/* Others */
		&(const struct rtwn_rf_prog){
			nitems(rtl8812au_rf0_regs4),
			rtl8812au_rf0_regs4,
			rtl8812au_rf0_vals4,
			{ 0 },
			NULL
		}
	},
	/* External 2GHz PA, type 0. */
	{
		nitems(rtl8812au_rf0_regs5),
		rtl8812au_rf0_regs5,
		rtl8812au_rf0_vals5_pa_g0,
		{ R12A_COND_GPA | R12A_COND_TYPE(0x0), 0 },
		/* Others. */
		&(const struct rtwn_rf_prog){
			nitems(rtl8812au_rf0_regs5),
			rtl8812au_rf0_regs5,
			rtl8812au_rf0_vals5,
			{ 0 },
			NULL
		}
	},
	{
		nitems(rtl8812au_rf0_regs6),
		rtl8812au_rf0_regs6,
		rtl8812au_rf0_vals6,
		{ 0 },
		NULL
	},
	/* External 5GHz PA, type 0. */
	{
		nitems(rtl8812au_rf0_regs7),
		rtl8812au_rf0_regs7,
		rtl8812au_rf0_vals7_pa_a0,
		{ R12A_COND_APA | R12A_COND_TYPE(0x0), 0 },
		/* External 5GHz PA, type 5. */
		&(const struct rtwn_rf_prog){
			nitems(rtl8812au_rf0_regs7),
			rtl8812au_rf0_regs7,
			rtl8812au_rf0_vals7_pa_a5,
			{ R12A_COND_APA | R12A_COND_TYPE(0x5), 0 },
			/* Others. */
			&(const struct rtwn_rf_prog){
				nitems(rtl8812au_rf0_regs7),
				rtl8812au_rf0_regs7,
				rtl8812au_rf0_vals7,
				{ 0 },
				NULL
			}
		}
	},
	/* External 5GHz PA, type 0 or 5. */
	{
		nitems(rtl8812au_rf0_regs8),
		rtl8812au_rf0_regs8,
		rtl8812au_rf0_vals8_pa_a0_a5,
		{
			R12A_COND_APA | R12A_COND_TYPE(0x0),
			R12A_COND_APA | R12A_COND_TYPE(0x5), 0
		},
		/* Others. */
		&(const struct rtwn_rf_prog){
			nitems(rtl8812au_rf0_regs8),
			rtl8812au_rf0_regs8,
			rtl8812au_rf0_vals8,
			{ 0 },
			NULL
		}
	},
	{
		nitems(rtl8812au_rf0_regs9),
		rtl8812au_rf0_regs9,
		rtl8812au_rf0_vals9,
		{ 0 },
		NULL
	},
	/* External 5GHz PA, type 0. */
	{
		nitems(rtl8812au_rf0_regs10),
		rtl8812au_rf0_regs10,
		rtl8812au_rf0_vals10_pa_a0,
		{ R12A_COND_APA | R12A_COND_TYPE(0x0), 0 },
		/* External 5GHz PA, type 5. */
		&(const struct rtwn_rf_prog){
			nitems(rtl8812au_rf0_regs10),
			rtl8812au_rf0_regs10,
			rtl8812au_rf0_vals10_pa_a5,
			{ R12A_COND_APA | R12A_COND_TYPE(0x5), 0 },
			/* Others. */
			&(const struct rtwn_rf_prog){
				nitems(rtl8812au_rf0_regs10),
				rtl8812au_rf0_regs10,
				rtl8812au_rf0_vals10,
				{ 0 },
				NULL
			}
		}
	},
	{
		nitems(rtl8812au_rf0_regs11),
		rtl8812au_rf0_regs11,
		rtl8812au_rf0_vals11,
		{ 0 },
		NULL
	},
	{ 0, NULL, NULL, { 0 },	NULL },
	/* RF path 2. */
	{
		nitems(rtl8812au_rf1_regs0),
		rtl8812au_rf1_regs0,
		rtl8812au_rf1_vals0,
		{ 0 },
		NULL
	},
	/* rtl8812au_rf[1] */
	/* External 2GHz LNA, type 0 or 5. */
	{
		nitems(rtl8812au_rf0_regs1),
		rtl8812au_rf0_regs1,
		rtl8812au_rf0_vals1_lna_g0_g5,
		{
			R12A_COND_GLNA | R12A_COND_TYPE(0x0),
			R12A_COND_GLNA | R12A_COND_TYPE(0x5), 0
		},
		/* Others. */
		&(const struct rtwn_rf_prog){
			nitems(rtl8812au_rf0_regs1),
			rtl8812au_rf0_regs1,
			rtl8812au_rf0_vals1,
			{ 0 },
			NULL
		}
	},
	/* rtl8812au_rf[2] */
	/* External 5GHz LNA, type 0. */
	{
		nitems(rtl8812au_rf0_regs2),
		rtl8812au_rf0_regs2,
		rtl8812au_rf0_vals2_lna_a0,
		{ R12A_COND_ALNA | R12A_COND_TYPE(0x0), 0 },
		/* Others. */
		&(const struct rtwn_rf_prog){
			nitems(rtl8812au_rf0_regs2),
			rtl8812au_rf0_regs2,
			rtl8812au_rf0_vals2,
			{ 0 },
			NULL
		}
	},
	{
		nitems(rtl8812au_rf1_regs3),
		rtl8812au_rf1_regs3,
		rtl8812au_rf1_vals3,
		{ 0 },
		NULL
	},
	/* rtl8812au_rf[4] */
	/* External 2GHz LNA, type 0 or 5. */
	{
		nitems(rtl8812au_rf0_regs4),
		rtl8812au_rf0_regs4,
		rtl8812au_rf0_vals4_lna_g0_g5,
		{
			R12A_COND_GLNA | R12A_COND_TYPE(0x0),
			R12A_COND_GLNA | R12A_COND_TYPE(0x5), 0
		},
		/* Others */
		&(const struct rtwn_rf_prog){
			nitems(rtl8812au_rf0_regs4),
			rtl8812au_rf0_regs4,
			rtl8812au_rf0_vals4,
			{ 0 },
			NULL
		}
	},
	/* rtl8812au_rf[5] */
	/* External 2GHz PA, type 0. */
	{
		nitems(rtl8812au_rf0_regs5),
		rtl8812au_rf0_regs5,
		rtl8812au_rf0_vals5_pa_g0,
		{ R12A_COND_GPA | R12A_COND_TYPE(0x0), 0 },
		/* Others. */
		&(const struct rtwn_rf_prog){
			nitems(rtl8812au_rf0_regs5),
			rtl8812au_rf0_regs5,
			rtl8812au_rf0_vals5,
			{ 0 },
			NULL
		}
	},
	{
		nitems(rtl8812au_rf0_regs6),
		rtl8812au_rf0_regs6,
		rtl8812au_rf1_vals6,
		{ 0 },
		NULL
	},
	/* External 5GHz PA, type 0. */
	{
		nitems(rtl8812au_rf0_regs7),
		rtl8812au_rf0_regs7,
		rtl8812au_rf0_vals7_pa_a0,
		{ R12A_COND_APA | R12A_COND_TYPE(0x0), 0 },
		/* External 5GHz PA, type 5. */
		&(const struct rtwn_rf_prog){
			nitems(rtl8812au_rf0_regs7),
			rtl8812au_rf0_regs7,
			rtl8812au_rf1_vals7_pa_a5,
			{ R12A_COND_APA | R12A_COND_TYPE(0x5), 0 },
			/* Others. */
			&(const struct rtwn_rf_prog){
				nitems(rtl8812au_rf0_regs7),
				rtl8812au_rf0_regs7,
				rtl8812au_rf0_vals7,
				{ 0 },
				NULL
			}
		}
	},
	/* External 5GHz PA, type 0 or 5. */
	{
		nitems(rtl8812au_rf0_regs8),
		rtl8812au_rf0_regs8,
		rtl8812au_rf1_vals8_pa_a0_a5,
		{
			R12A_COND_APA | R12A_COND_TYPE(0x0),
			R12A_COND_APA | R12A_COND_TYPE(0x5), 0
		},
		/* Others. */
		&(const struct rtwn_rf_prog){
			nitems(rtl8812au_rf0_regs8),
			rtl8812au_rf0_regs8,
			rtl8812au_rf0_vals8,
			{ 0 },
			NULL
		}
	},
	{
		nitems(rtl8812au_rf0_regs9) - 1,
		rtl8812au_rf0_regs9,
		rtl8812au_rf0_vals9,
		{ 0 },
		NULL
	},

	/* External 2GHz or 5GHz PA, type 0. */
	{
		nitems(rtl8812au_rf0_regs10),
		rtl8812au_rf0_regs10,
		rtl8812au_rf1_vals10_pa_g0_a0,
		{
			R12A_COND_GPA | R12A_COND_TYPE(0x0),
			R12A_COND_APA | R12A_COND_TYPE(0x0), 0
		},
		/* External 5GHz PA, type 5. */
		&(const struct rtwn_rf_prog){
			nitems(rtl8812au_rf0_regs10),
			rtl8812au_rf0_regs10,
			rtl8812au_rf1_vals10_pa_a5,
			{ R12A_COND_APA | R12A_COND_TYPE(0x5), 0 },
			/* Others. */
			&(const struct rtwn_rf_prog){
				nitems(rtl8812au_rf0_regs10),
				rtl8812au_rf0_regs10,
				rtl8812au_rf0_vals10,
				{ 0 },
				NULL
			}
		}
	},
	{
		1,
		rtl8812au_rf0_regs11,
		rtl8812au_rf0_vals11,
		{ 0 },
		NULL
	},
	{ 0, NULL, NULL, { 0 }, NULL }
};


/*
 * Registers to save before IQ calibration.
 */
static const uint16_t r12a_iq_bb_regs[] = {
	0x520, 0x550, 0x808, 0xa04, 0x90c, 0xc00, 0xe00, 0x838, 0x82c
};

static const uint16_t r12a_iq_afe_regs[] = {
	0xc5c, 0xc60, 0xc64, 0xc68, 0xcb0, 0xcb4, 0xe5c, 0xe60, 0xe64,
	0xe68, 0xeb0, 0xeb4
};

static const uint8_t r12a_iq_rf_regs[] = {
	0x65, 0x8f, 0x0
};

#endif	/* R12A_PRIV_H */
