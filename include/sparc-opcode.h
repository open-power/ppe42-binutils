/* to sanitize this file, grep -v v9 < sparc-opcode.h > clean-sparc-opcode.h */

/* Table of opcodes for the sparc.
	Copyright (C) 1989, 1991 Free Software Foundation, Inc.

This file is part of GAS, the GNU Assembler, and GDB, the GNU disassembler.

GAS/GDB is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2, or (at your option)
any later version.

GAS/GDB is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with GAS or GDB; see the file COPYING.	If not, write to
the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.	*/

 /* FIXME-someday: perhaps the ,a's and such should be embedded in the
    instruction's name rather than the args.  This would make gas faster, pinsn
    slower, but would mess up some macros a bit.  xoxorich. */

#if !defined(__STDC__) && !defined(const)
#define const
#endif

/*
 * Structure of an opcode table entry.
 */
enum sparc_architecture {
	v6 = 0,
	v7,
	cypress,
	v8,
	v9,
};

static const char *architecture_pname[] = {
	"v6",
	"v7",
	"cypress",
	"v8",
	"v9",
	NULL,
};

struct sparc_opcode {
	const char *name;
	unsigned long match;	/* Bits that must be set. */
	unsigned long lose;	/* Bits that must not be set. */
	const char *args;
 /* This was called "delayed" in versions before the flags. */
	char flags;
	enum sparc_architecture architecture;
};

#define	F_DELAYED	1	/* Delayed branch */
#define	F_ALIAS		2	/* Alias for a "real" instruction */

/*

All sparc opcodes are 32 bits, except for the `set' instruction (really a
macro), which is 64 bits. It is handled as a special case.

The match component is a mask saying which bits must match a particular
opcode in order for an instruction to be an instance of that opcode.

The args component is a string containing one character for each operand of the
instruction.

Kinds of operands:
	#	Number used by optimizer.	It is ignored.
	1	rs1 register.
	2	rs2 register.
	d	rd register.
	e	frs1 floating point register.
	f	frs2 floating point register.
	j	frs3 floating point register. (v9)
	g	frsd floating point register.
	b	crs1 coprocessor register
	c	crs2 coprocessor register
	D	crsd coprocessor register
	m	alternate space register (asr) in rd
	M	alternate space register (asr) in rs1
	h	22 high bits.
	I	11 bit Immediate. (v9)
	i	13 bit Immediate.
	k	2+14 bit PC relative immediate. (v9)
	G	19 bit PC relative immediate. (v9)
	l	22 bit PC relative immediate.
	L	30 bit PC relative immediate.
	a	Annul.	The annul bit is set.
	A	Alternate address space. Stored as 8 bits.
	C	Coprocessor state register.
	F	floating point state register.
	p	Processor state register.
	N	Branch predict clear ",pn" (v9)
	T	Branch predict set ",pt" (v9)
	z	icc. (v9)
	Z	xcc. (v9)
	q	Floating point queue.
	r	Single register that is both rs1 and rsd.
	Q	Coprocessor queue.
	S	Special case.
	t	Trap base register.
	w	Window invalid mask register.
	y	Y register.
	Y	%amr (v9?)
	P	%pc.  (v9)
	E	%modes.  (v9)
	W	%tick.	(v9)
	6	fcc0. (v9)
	7	fcc1. (v9)
	8	fcc2. (v9)
	9	fcc3. (v9)

The following chars are unused: (note: ,[] are used as punctuation)
[nosuvxBHIJORUVX3450]

*/

/* The order of the opcodes in this table is significant:
	
	* The assembler requires that all instances of the same mnemonic must
	be consecutive.	If they aren't, the assembler will bomb at runtime.

	* The disassembler should not care about the order of the opcodes.

*/

#define OP2(x)		(((x)&0x7) << 22) /* op2 field of format2 insns */
#define OP3(x)		(((x)&0x3f) << 19) /* op3 field of format3 insns */
#define OP(x)		(((x)&0x3) << 30) /* op field of all insns */
#define OPF(x)		(((x)&0x1ff) << 5) /* opf field of float insns */
#define OPF_LOW(x)	OPF((x)&0xf) /* v9 */
#define F3F(x, y, z)	(OP(x) | OP3(y) | OPF(z)) /* format3 float insns */
#define F3I(x)		(((x)&0x1) << 13) /* immediate field of format 3 insns */
#define F2(x, y)	(OP(x) | OP2(y)) /* format 2 insns */
#define F3(x, y, z)	(OP(x) | OP3(y) | F3I(z)) /* format3 insns */
#define F1(x)		(OP(x))
#define DISP30(x)	((x)&0x3fffffff)
#define ASI(x)		(((x)&0xff) << 5) /* asi field of format3 insns */
#define RS2(x)		((x)&0x1f) /* rs2 field */
#define SIMM13(x)	((x)&0x1fff) /* simm13 field */
#define RD(x)		(((x)&0x1f) << 25) /* destination register field */
#define RS1(x)		(((x)&0x1f) << 14) /* rs1 field */
#define ASI_RS2(x)	(SIMM13(x))

#define ANNUL	(1<<29)
#define BPRED	(1<<21)	/* v9 */
#define	IMMED	F3I(1)
#define RD_G0	RD(~0)
#define	RS1_G0	RS1(~0)
#define	RS2_G0	RS2(~0)

#define COND(x)		(((x)&0xf)<<25)
#define MCOND(x)	(((x)>>11)&(0xf<<14))	/* v9 */

#define CONDA	(COND(0x8))
#define CONDCC	(COND(0xd))
#define CONDCS	(COND(0x5))
#define CONDE	(COND(0x1))
#define CONDG	(COND(0xa))
#define CONDGE	(COND(0xb))
#define CONDGU	(COND(0xc))
#define CONDL	(COND(0x3))
#define CONDLE	(COND(0x2))
#define CONDLEU	(COND(0x4))
#define CONDN	(COND(0x0))
#define CONDNE	(COND(0x9))
#define CONDNEG	(COND(0x6))
#define CONDPOS	(COND(0xe))
#define CONDVC	(COND(0xf))
#define CONDVS	(COND(0x7))

#define CONDNZ	CONDNE
#define CONDZ	CONDE
#define CONDGEU	CONDCC
#define CONDLU	CONDCS

#define FCONDA		(COND(0x8))
#define FCONDE		(COND(0x9))
#define FCONDG		(COND(0x6))
#define FCONDGE		(COND(0xb))
#define FCONDL		(COND(0x4))
#define FCONDLE		(COND(0xd))
#define FCONDLG		(COND(0x2))
#define FCONDN		(COND(0x0))
#define FCONDNE		(COND(0x1))
#define FCONDO		(COND(0xf))
#define FCONDU		(COND(0x7))
#define FCONDUE		(COND(0xa))
#define FCONDUG		(COND(0x5))
#define FCONDUGE	(COND(0xc))
#define FCONDUL		(COND(0x3))
#define FCONDULE	(COND(0xe))

#define FCONDNZ	FCONDNE
#define FCONDZ	FCONDE

#define ICC (0)	/* v9 */
#define XCC (1<<11) /* v9 */
#define FCC(x)	(((x)&0x3)<<11) /* v9 */
#define FBFCC(x)	(((x)&0x3)<<19)	/* v9 */

static const struct sparc_opcode sparc_opcodes[] = {

{ "ld",	F3(3, 0x00, 0), F3(~3, ~0x00, ~0),		"[1+2],d", 0, v6 },
{ "ld",	F3(3, 0x00, 0), F3(~3, ~0x00, ~0)|RS2_G0,	"[1],d", 0, v6 }, /* ld [rs1+%g0],d */
{ "ld",	F3(3, 0x00, 1), F3(~3, ~0x00, ~1),		"[1+i],d", 0, v6 },
{ "ld",	F3(3, 0x00, 1), F3(~3, ~0x00, ~1),		"[i+1],d", 0, v6 },
{ "ld",	F3(3, 0x00, 1), F3(~3, ~0x00, ~1)|RS1_G0,	"[i],d", 0, v6 },
{ "ld",	F3(3, 0x00, 1), F3(~3, ~0x00, ~1)|SIMM13(~0),	"[1],d", 0, v6 }, /* ld [rs1+0],d */
{ "ld",	F3(3, 0x20, 0), F3(~3, ~0x20, ~0),		"[1+2],g", 0, v6 },
{ "ld",	F3(3, 0x20, 0), F3(~3, ~0x20, ~0)|RS2_G0,	"[1],g", 0, v6 }, /* ld [rs1+%g0],d */
{ "ld",	F3(3, 0x20, 1), F3(~3, ~0x20, ~1),		"[1+i],g", 0, v6 },
{ "ld",	F3(3, 0x20, 1), F3(~3, ~0x20, ~1),		"[i+1],g", 0, v6 },
{ "ld",	F3(3, 0x20, 1), F3(~3, ~0x20, ~1)|RS1_G0,	"[i],g", 0, v6 },
{ "ld",	F3(3, 0x20, 1), F3(~3, ~0x20, ~1)|SIMM13(~0),	"[1],g", 0, v6 }, /* ld [rs1+0],d */
{ "ld",	F3(3, 0x21, 0), F3(~3, ~0x21, ~0),		"[1+2],F", 0, v6 },
{ "ld",	F3(3, 0x21, 0), F3(~3, ~0x21, ~0)|RS2_G0,	"[1],F", 0, v6 }, /* ld [rs1+%g0],d */
{ "ld",	F3(3, 0x21, 1), F3(~3, ~0x21, ~1),		"[1+i],F", 0, v6 },
{ "ld",	F3(3, 0x21, 1), F3(~3, ~0x21, ~1),		"[i+1],F", 0, v6 },
{ "ld",	F3(3, 0x21, 1), F3(~3, ~0x21, ~1)|RS1_G0,	"[i],F", 0, v6 },
{ "ld",	F3(3, 0x21, 1), F3(~3, ~0x21, ~1)|SIMM13(~0),	"[1],F", 0, v6 }, /* ld [rs1+0],d */
{ "ld",	F3(3, 0x30, 0), F3(~3, ~0x30, ~0),		"[1+2],D", 0, v6 },
{ "ld",	F3(3, 0x30, 0), F3(~3, ~0x30, ~0)|RS2_G0,	"[1],D", 0, v6 }, /* ld [rs1+%g0],d */
{ "ld",	F3(3, 0x30, 1), F3(~3, ~0x30, ~1),		"[1+i],D", 0, v6 },
{ "ld",	F3(3, 0x30, 1), F3(~3, ~0x30, ~1),		"[i+1],D", 0, v6 },
{ "ld",	F3(3, 0x30, 1), F3(~3, ~0x30, ~1)|RS1_G0,	"[i],D", 0, v6 },
{ "ld",	F3(3, 0x30, 1), F3(~3, ~0x30, ~1)|SIMM13(~0),	"[1],D", 0, v6 }, /* ld [rs1+0],d */
{ "ld",	F3(3, 0x31, 0), F3(~3, ~0x31, ~0),		"[1+2],C", 0, v6 },
{ "ld",	F3(3, 0x31, 0), F3(~3, ~0x31, ~0)|RS2_G0,	"[1],C", 0, v6 }, /* ld [rs1+%g0],d */
{ "ld",	F3(3, 0x31, 1), F3(~3, ~0x31, ~1),		"[1+i],C", 0, v6 },
{ "ld",	F3(3, 0x31, 1), F3(~3, ~0x31, ~1),		"[i+1],C", 0, v6 },
{ "ld",	F3(3, 0x31, 1), F3(~3, ~0x31, ~1)|RS1_G0,	"[i],C", 0, v6 },
{ "ld",	F3(3, 0x31, 1), F3(~3, ~0x31, ~1)|SIMM13(~0),	"[1],C", 0, v6 }, /* ld [rs1+0],d */

 /* FIXME-v9: combine ld, lduw, & ldw in macros. */
{ "ldw",	F3(3, 0x00, 0), F3(~3, ~0x00, ~0),		"[1+2],d", F_ALIAS, v9 }, /* ldw === ld */
{ "ldw",	F3(3, 0x00, 0), F3(~3, ~0x00, ~0)|RS2_G0,	"[1],d", F_ALIAS, v9 }, /* ld [rs1+%g0],d */
{ "ldw",	F3(3, 0x00, 1), F3(~3, ~0x00, ~1),		"[1+i],d", F_ALIAS, v9 },
{ "ldw",	F3(3, 0x00, 1), F3(~3, ~0x00, ~1),		"[i+1],d", F_ALIAS, v9 },
{ "ldw",	F3(3, 0x00, 1), F3(~3, ~0x00, ~1)|RS1_G0,	"[i],d", F_ALIAS, v9 },
{ "ldw",	F3(3, 0x00, 1), F3(~3, ~0x00, ~1)|SIMM13(~0),	"[1],d", F_ALIAS, v9 }, /* ld [rs1+0],d */
{ "ldw",	F3(3, 0x20, 0), F3(~3, ~0x20, ~0),		"[1+2],g", F_ALIAS, v9 },
{ "ldw",	F3(3, 0x20, 0), F3(~3, ~0x20, ~0)|RS2_G0,	"[1],g", F_ALIAS, v9 }, /* ld [rs1+%g0],d */
{ "ldw",	F3(3, 0x20, 1), F3(~3, ~0x20, ~1),		"[1+i],g", F_ALIAS, v9 },
{ "ldw",	F3(3, 0x20, 1), F3(~3, ~0x20, ~1),		"[i+1],g", F_ALIAS, v9 },
{ "ldw",	F3(3, 0x20, 1), F3(~3, ~0x20, ~1)|RS1_G0,	"[i],g", F_ALIAS, v9 },
{ "ldw",	F3(3, 0x20, 1), F3(~3, ~0x20, ~1)|SIMM13(~0),	"[1],g", F_ALIAS, v9 }, /* ld [rs1+0],d */
{ "ldw",	F3(3, 0x21, 0), F3(~3, ~0x21, ~0),		"[1+2],F", F_ALIAS, v9 },
{ "ldw",	F3(3, 0x21, 0), F3(~3, ~0x21, ~0)|RS2_G0,	"[1],F", F_ALIAS, v9 }, /* ld [rs1+%g0],d */
{ "ldw",	F3(3, 0x21, 1), F3(~3, ~0x21, ~1),		"[1+i],F", F_ALIAS, v9 },
{ "ldw",	F3(3, 0x21, 1), F3(~3, ~0x21, ~1),		"[i+1],F", F_ALIAS, v9 },
{ "ldw",	F3(3, 0x21, 1), F3(~3, ~0x21, ~1)|RS1_G0,	"[i],F", F_ALIAS, v9 },
{ "ldw",	F3(3, 0x21, 1), F3(~3, ~0x21, ~1)|SIMM13(~0),	"[1],F", F_ALIAS, v9 }, /* ld [rs1+0],d */
{ "ldw",	F3(3, 0x30, 0), F3(~3, ~0x30, ~0),		"[1+2],D", F_ALIAS, v9 },
{ "ldw",	F3(3, 0x30, 0), F3(~3, ~0x30, ~0)|RS2_G0,	"[1],D", F_ALIAS, v9 }, /* ld [rs1+%g0],d */
{ "ldw",	F3(3, 0x30, 1), F3(~3, ~0x30, ~1),		"[1+i],D", F_ALIAS, v9 },
{ "ldw",	F3(3, 0x30, 1), F3(~3, ~0x30, ~1),		"[i+1],D", F_ALIAS, v9 },
{ "ldw",	F3(3, 0x30, 1), F3(~3, ~0x30, ~1)|RS1_G0,	"[i],D", F_ALIAS, v9 },
{ "ldw",	F3(3, 0x30, 1), F3(~3, ~0x30, ~1)|SIMM13(~0),	"[1],D", F_ALIAS, v9 }, /* ld [rs1+0],d */
{ "ldw",	F3(3, 0x31, 0), F3(~3, ~0x31, ~0),		"[1+2],C", F_ALIAS, v9 },
{ "ldw",	F3(3, 0x31, 0), F3(~3, ~0x31, ~0)|RS2_G0,	"[1],C", F_ALIAS, v9 }, /* ld [rs1+%g0],d */
{ "ldw",	F3(3, 0x31, 1), F3(~3, ~0x31, ~1),		"[1+i],C", F_ALIAS, v9 },
{ "ldw",	F3(3, 0x31, 1), F3(~3, ~0x31, ~1),		"[i+1],C", F_ALIAS, v9 },
{ "ldw",	F3(3, 0x31, 1), F3(~3, ~0x31, ~1)|RS1_G0,	"[i],C", F_ALIAS, v9 },
{ "ldw",	F3(3, 0x31, 1), F3(~3, ~0x31, ~1)|SIMM13(~0),	"[1],C", F_ALIAS, v9 }, /* ld [rs1+0],d */

{ "lduw",	F3(3, 0x00, 0), F3(~3, ~0x00, ~0),		"[1+2],d", F_ALIAS, v9 }, /* lduw === ld */
{ "lduw",	F3(3, 0x00, 0), F3(~3, ~0x00, ~0)|RS2_G0,	"[1],d", F_ALIAS, v9 }, /* ld [rs1+%g0],d */
{ "lduw",	F3(3, 0x00, 1), F3(~3, ~0x00, ~1),		"[1+i],d", F_ALIAS, v9 },
{ "lduw",	F3(3, 0x00, 1), F3(~3, ~0x00, ~1),		"[i+1],d", F_ALIAS, v9 },
{ "lduw",	F3(3, 0x00, 1), F3(~3, ~0x00, ~1)|RS1_G0,	"[i],d", F_ALIAS, v9 },
{ "lduw",	F3(3, 0x00, 1), F3(~3, ~0x00, ~1)|SIMM13(~0),	"[1],d", F_ALIAS, v9 }, /* ld [rs1+0],d */
{ "lduw",	F3(3, 0x20, 0), F3(~3, ~0x20, ~0),		"[1+2],g", F_ALIAS, v9 },
{ "lduw",	F3(3, 0x20, 0), F3(~3, ~0x20, ~0)|RS2_G0,	"[1],g", F_ALIAS, v9 }, /* ld [rs1+%g0],d */
{ "lduw",	F3(3, 0x20, 1), F3(~3, ~0x20, ~1),		"[1+i],g", F_ALIAS, v9 },
{ "lduw",	F3(3, 0x20, 1), F3(~3, ~0x20, ~1),		"[i+1],g", F_ALIAS, v9 },
{ "lduw",	F3(3, 0x20, 1), F3(~3, ~0x20, ~1)|RS1_G0,	"[i],g", F_ALIAS, v9 },
{ "lduw",	F3(3, 0x20, 1), F3(~3, ~0x20, ~1)|SIMM13(~0),	"[1],g", F_ALIAS, v9 }, /* ld [rs1+0],d */
{ "lduw",	F3(3, 0x21, 0), F3(~3, ~0x21, ~0),		"[1+2],F", F_ALIAS, v9 },
{ "lduw",	F3(3, 0x21, 0), F3(~3, ~0x21, ~0)|RS2_G0,	"[1],F", F_ALIAS, v9 }, /* ld [rs1+%g0],d */
{ "lduw",	F3(3, 0x21, 1), F3(~3, ~0x21, ~1),		"[1+i],F", F_ALIAS, v9 },
{ "lduw",	F3(3, 0x21, 1), F3(~3, ~0x21, ~1),		"[i+1],F", F_ALIAS, v9 },
{ "lduw",	F3(3, 0x21, 1), F3(~3, ~0x21, ~1)|RS1_G0,	"[i],F", F_ALIAS, v9 },
{ "lduw",	F3(3, 0x21, 1), F3(~3, ~0x21, ~1)|SIMM13(~0),	"[1],F", F_ALIAS, v9 }, /* ld [rs1+0],d */
{ "lduw",	F3(3, 0x30, 0), F3(~3, ~0x30, ~0),		"[1+2],D", F_ALIAS, v9 },
{ "lduw",	F3(3, 0x30, 0), F3(~3, ~0x30, ~0)|RS2_G0,	"[1],D", F_ALIAS, v9 }, /* ld [rs1+%g0],d */
{ "lduw",	F3(3, 0x30, 1), F3(~3, ~0x30, ~1),		"[1+i],D", F_ALIAS, v9 },
{ "lduw",	F3(3, 0x30, 1), F3(~3, ~0x30, ~1),		"[i+1],D", F_ALIAS, v9 },
{ "lduw",	F3(3, 0x30, 1), F3(~3, ~0x30, ~1)|RS1_G0,	"[i],D", F_ALIAS, v9 },
{ "lduw",	F3(3, 0x30, 1), F3(~3, ~0x30, ~1)|SIMM13(~0),	"[1],D", F_ALIAS, v9 }, /* ld [rs1+0],d */
{ "lduw",	F3(3, 0x31, 0), F3(~3, ~0x31, ~0),		"[1+2],C", F_ALIAS, v9 },
{ "lduw",	F3(3, 0x31, 0), F3(~3, ~0x31, ~0)|RS2_G0,	"[1],C", F_ALIAS, v9 }, /* ld [rs1+%g0],d */
{ "lduw",	F3(3, 0x31, 1), F3(~3, ~0x31, ~1),		"[1+i],C", F_ALIAS, v9 },
{ "lduw",	F3(3, 0x31, 1), F3(~3, ~0x31, ~1),		"[i+1],C", F_ALIAS, v9 },
{ "lduw",	F3(3, 0x31, 1), F3(~3, ~0x31, ~1)|RS1_G0,	"[i],C", F_ALIAS, v9 },
{ "lduw",	F3(3, 0x31, 1), F3(~3, ~0x31, ~1)|SIMM13(~0),	"[1],C", F_ALIAS, v9 }, /* ld [rs1+0],d */

{ "lda",	F3(3, 0x10, 0), F3(~3, ~0x10, ~0),		"[1+2]A,d", 0, v6 },
{ "lda",	F3(3, 0x10, 0), F3(~3, ~0x10, ~0)|RS2_G0,	"[1]A,d", 0, v6 }, /* lda [rs1+%g0],d */

{ "ldd",	F3(3, 0x03, 0), F3(~3, ~0x03, ~0)|ASI(~0),	"[1+2],d", 0, v6 },
{ "ldd",	F3(3, 0x03, 0), F3(~3, ~0x03, ~0)|ASI_RS2(~0),	"[1],d", 0, v6 }, /* ldd [rs1+%g0],d */
{ "ldd",	F3(3, 0x03, 1), F3(~3, ~0x03, ~1),		"[1+i],d", 0, v6 },
{ "ldd",	F3(3, 0x03, 1), F3(~3, ~0x03, ~1),		"[i+1],d", 0, v6 },
{ "ldd",	F3(3, 0x03, 1), F3(~3, ~0x03, ~1)|RS1_G0,	"[i],d", 0, v6 },
{ "ldd",	F3(3, 0x03, 1), F3(~3, ~0x03, ~1)|SIMM13(~0),	"[1],d", 0, v6 }, /* ldd [rs1+0],d */
{ "ldd",	F3(3, 0x23, 0), F3(~3, ~0x23, ~0)|ASI(~0),	"[1+2],g", 0, v6 },
{ "ldd",	F3(3, 0x23, 0), F3(~3, ~0x23, ~0)|ASI_RS2(~0),	"[1],g", 0, v6 }, /* ldd [rs1+%g0],d */
{ "ldd",	F3(3, 0x23, 1), F3(~3, ~0x23, ~1),		"[1+i],g", 0, v6 },
{ "ldd",	F3(3, 0x23, 1), F3(~3, ~0x23, ~1),		"[i+1],g", 0, v6 },
{ "ldd",	F3(3, 0x23, 1), F3(~3, ~0x23, ~1)|RS1_G0,	"[i],g", 0, v6 },
{ "ldd",	F3(3, 0x23, 1), F3(~3, ~0x23, ~1)|SIMM13(~0),	"[1],g", 0, v6 }, /* ldd [rs1+0],d */
{ "ldd",	F3(3, 0x33, 0), F3(~3, ~0x33, ~0)|ASI(~0),	"[1+2],D", 0, v6 },
{ "ldd",	F3(3, 0x33, 0), F3(~3, ~0x33, ~0)|ASI_RS2(~0),	"[1],D", 0, v6 }, /* ldd [rs1+%g0],d */
{ "ldd",	F3(3, 0x33, 1), F3(~3, ~0x33, ~1),		"[1+i],D", 0, v6 },
{ "ldd",	F3(3, 0x33, 1), F3(~3, ~0x33, ~1),		"[i+1],D", 0, v6 },
{ "ldd",	F3(3, 0x33, 1), F3(~3, ~0x33, ~1)|RS1_G0,	"[i],D", 0, v6 },
{ "ldd",	F3(3, 0x33, 1), F3(~3, ~0x33, ~1)|SIMM13(~0),	"[1],D", 0, v6 }, /* ldd [rs1+0],d */
{ "ldsb",	F3(3, 0x09, 0), F3(~3, ~0x09, ~0)|ASI(~0),	"[1+2],d", 0, v6 },
{ "ldsb",	F3(3, 0x09, 0), F3(~3, ~0x09, ~0)|ASI_RS2(~0),	"[1],d", 0, v6 }, /* ldsb [rs1+%g0],d */
{ "ldsb",	F3(3, 0x09, 1), F3(~3, ~0x09, ~1),		"[1+i],d", 0, v6 },
{ "ldsb",	F3(3, 0x09, 1), F3(~3, ~0x09, ~1),		"[i+1],d", 0, v6 },
{ "ldsb",	F3(3, 0x09, 1), F3(~3, ~0x09, ~1)|RS1_G0,	"[i],d", 0, v6 },
{ "ldsb",	F3(3, 0x09, 1), F3(~3, ~0x09, ~1)|SIMM13(~0),	"[1],d", 0, v6 }, /* ldsb [rs1+0],d */
{ "ldsh",	F3(3, 0x0a, 0), F3(~3, ~0x0a, ~0)|ASI_RS2(~0),	"[1],d", 0, v6 }, /* ldsh [rs1+%g0],d */
{ "ldsh",	F3(3, 0x0a, 0), F3(~3, ~0x0a, ~0)|ASI(~0),	"[1+2],d", 0, v6 },
{ "ldsh",	F3(3, 0x0a, 1), F3(~3, ~0x0a, ~1),		"[1+i],d", 0, v6 },
{ "ldsh",	F3(3, 0x0a, 1), F3(~3, ~0x0a, ~1),		"[i+1],d", 0, v6 },
{ "ldsh",	F3(3, 0x0a, 1), F3(~3, ~0x0a, ~1)|RS1_G0,	"[i],d", 0, v6 },
{ "ldsh",	F3(3, 0x0a, 1), F3(~3, ~0x0a, ~1)|SIMM13(~0),	"[1],d", 0, v6 }, /* ldsh [rs1+0],d */
{ "ldstub",	F3(3, 0x0d, 0), F3(~3, ~0x0d, ~0)|ASI(~0),	"[1+2],d", 0, v6 },
{ "ldstub",	F3(3, 0x0d, 0), F3(~3, ~0x0d, ~0)|ASI_RS2(~0),	"[1],d", 0, v6 }, /* ldstub [rs1+%g0],d */
{ "ldstub",	F3(3, 0x0d, 1), F3(~3, ~0x0d, ~1),		"[1+i],d", 0, v6 },
{ "ldstub",	F3(3, 0x0d, 1), F3(~3, ~0x0d, ~1),		"[i+1],d", 0, v6 },
{ "ldstub",	F3(3, 0x0d, 1), F3(~3, ~0x0d, ~1)|RS1_G0,	"[i],d", 0, v6 },
{ "ldsw",	F3(3, 0x08, 0), F3(~3, ~0x08, ~0)|ASI(~0),	"[1+2],d", 0, v9 },
{ "ldsw",	F3(3, 0x08, 0), F3(~3, ~0x08, ~0)|ASI_RS2(~0),	"[1],d", 0, v9 }, /* ldsw [rs1+%g0],d */
{ "ldsw",	F3(3, 0x08, 1), F3(~3, ~0x08, ~1),		"[1+i],d", 0, v9 },
{ "ldsw",	F3(3, 0x08, 1), F3(~3, ~0x08, ~1),		"[i+1],d", 0, v9 },
{ "ldsw",	F3(3, 0x08, 1), F3(~3, ~0x08, ~1)|RS1_G0,	"[i],d", 0, v9 },
{ "ldsw",	F3(3, 0x08, 1), F3(~3, ~0x08, ~1)|SIMM13(~0),	"[1],d", 0, v9 }, /* ldsw [rs1+0],d */
{ "ldub",	F3(3, 0x01, 0), F3(~3, ~0x01, ~0)|ASI(~0),	"[1+2],d", 0, v6 },
{ "ldub",	F3(3, 0x01, 0), F3(~3, ~0x01, ~0)|ASI_RS2(~0),	"[1],d", 0, v6 }, /* ldub [rs1+%g0],d */
{ "ldub",	F3(3, 0x01, 1), F3(~3, ~0x01, ~1),		"[1+i],d", 0, v6 },
{ "ldub",	F3(3, 0x01, 1), F3(~3, ~0x01, ~1),		"[i+1],d", 0, v6 },
{ "ldub",	F3(3, 0x01, 1), F3(~3, ~0x01, ~1)|RS1_G0,	"[i],d", 0, v6 },
{ "ldub",	F3(3, 0x01, 1), F3(~3, ~0x01, ~1)|SIMM13(~0),	"[1],d", 0, v6 }, /* ldub [rs1+0],d */
{ "lduh",	F3(3, 0x02, 0), F3(~3, ~0x02, ~0)|ASI(~0),	"[1+2],d", 0, v6 },
{ "lduh",	F3(3, 0x02, 0), F3(~3, ~0x02, ~0)|ASI_RS2(~0),	"[1],d", 0, v6 }, /* lduh [rs1+%g0],d */
{ "lduh",	F3(3, 0x02, 1), F3(~3, ~0x02, ~1),		"[1+i],d", 0, v6 },
{ "lduh",	F3(3, 0x02, 1), F3(~3, ~0x02, ~1),		"[i+1],d", 0, v6 },
{ "lduh",	F3(3, 0x02, 1), F3(~3, ~0x02, ~1)|RS1_G0,	"[i],d", 0, v6 },
{ "lduh",	F3(3, 0x02, 1), F3(~3, ~0x02, ~1)|SIMM13(~0),	"[1],d", 0, v6 }, /* lduh [rs1+0],d */

{ "ldx",	F3(3, 0x0b, 0), F3(~3, ~0x0b, ~0)|ASI(~0),	"[1+2],d", 0, v9 },
{ "ldx",	F3(3, 0x0b, 0), F3(~3, ~0x0b, ~0)|ASI_RS2(~0),	"[1],d", 0, v9 }, /* ldx [rs1+%g0],d */
{ "ldx",	F3(3, 0x0b, 1), F3(~3, ~0x0b, ~1),		"[1+i],d", 0, v9 },
{ "ldx",	F3(3, 0x0b, 1), F3(~3, ~0x0b, ~1),		"[i+1],d", 0, v9 },
{ "ldx",	F3(3, 0x0b, 1), F3(~3, ~0x0b, ~1)|RS1_G0,	"[i],d", 0, v9 },
{ "ldx",	F3(3, 0x0b, 1), F3(~3, ~0x0b, ~1)|SIMM13(~0),	"[1],d", 0, v9 }, /* ldx [rs1+0],d */
{ "ldx",	F3(3, 0x29, 0), F3(~3, ~0x29, ~0),		"[1+2],F", 0, v9 },
{ "ldx",	F3(3, 0x29, 0), F3(~3, ~0x29, ~0)|RS2_G0,	"[1],F", 0, v9 }, /* ld [rs1+%g0],d */
{ "ldx",	F3(3, 0x29, 1), F3(~3, ~0x29, ~1),		"[1+i],F", 0, v9 },
{ "ldx",	F3(3, 0x29, 1), F3(~3, ~0x29, ~1),		"[i+1],F", 0, v9 },
{ "ldx",	F3(3, 0x29, 1), F3(~3, ~0x29, ~1)|RS1_G0,	"[i],F", 0, v9 },
{ "ldx",	F3(3, 0x29, 1), F3(~3, ~0x29, ~1)|SIMM13(~0),	"[1],F", 0, v9 }, /* ld [rs1+0],d */

{ "ldda",	F3(3, 0x13, 0), F3(~3, ~0x13, ~0),		"[1+2]A,d", 0, v6 },
{ "ldda",	F3(3, 0x13, 0), F3(~3, ~0x13, ~0)|RS2_G0,	"[1]A,d", 0, v6 }, /* ldda [rs1+%g0],d */
{ "ldsba",	F3(3, 0x19, 0), F3(~3, ~0x19, ~0),		"[1+2]A,d", 0, v6 },
{ "ldsba",	F3(3, 0x19, 0), F3(~3, ~0x19, ~0)|RS2_G0,	"[1]A,d", 0, v6 }, /* ldsba [rs1+%g0],d */
{ "ldsha",	F3(3, 0x1a, 0), F3(~3, ~0x1a, ~0),		"[1+2]A,d", 0, v6 },
{ "ldsha",	F3(3, 0x1a, 0), F3(~3, ~0x1a, ~0)|RS2_G0,	"[1]A,d", 0, v6 }, /* ldsha [rs1+%g0],d */
{ "ldstuba",	F3(3, 0x1d, 0), F3(~3, ~0x1d, ~0),		"[1+2]A,d", 0, v6 },
{ "ldstuba",	F3(3, 0x1d, 0), F3(~3, ~0x1d, ~0)|RS2_G0,	"[1]A,d", 0, v6 }, /* ldstuba [rs1+%g0],d */
{ "ldswa",	F3(3, 0x18, 0), F3(~3, ~0x18, ~0),		"[1+2]A,d", 0, v9 }, /* lduwa === lda */
{ "ldswa",	F3(3, 0x18, 0), F3(~3, ~0x18, ~0)|RS2_G0,	"[1]A,d", 0, v9 }, /* lda [rs1+%g0],d */
{ "lduba",	F3(3, 0x11, 0), F3(~3, ~0x11, ~0),		"[1+2]A,d", 0, v6 },
{ "lduba",	F3(3, 0x11, 0), F3(~3, ~0x11, ~0)|RS2_G0,	"[1]A,d", 0, v6 }, /* lduba [rs1+%g0],d */
{ "lduha",	F3(3, 0x12, 0), F3(~3, ~0x12, ~0),		"[1+2]A,d", 0, v6 },
{ "lduha",	F3(3, 0x12, 0), F3(~3, ~0x12, ~0)|RS2_G0,	"[1]A,d", 0, v6 }, /* lduha [rs1+%g0],d */
{ "lduwa",	F3(3, 0x10, 0), F3(~3, ~0x10, ~0),		"[1+2]A,d", F_ALIAS, v9 }, /* lduwa === lda */
{ "lduwa",	F3(3, 0x10, 0), F3(~3, ~0x10, ~0)|RS2_G0,	"[1]A,d", F_ALIAS, v9 }, /* lda [rs1+%g0],d */
{ "ldxa",	F3(3, 0x1b, 0), F3(~3, ~0x1b, ~0),		"[1+2]A,d", 0, v9 }, /* lduwa === lda */
{ "ldxa",	F3(3, 0x1b, 0), F3(~3, ~0x1b, ~0)|RS2_G0,	"[1]A,d", 0, v9 }, /* lda [rs1+%g0],d */

{ "st",	F3(3, 0x04, 0), F3(~3, ~0x04, ~0)|ASI(~0),		"d,[1+2]", 0, v6 },
{ "st",	F3(3, 0x04, 0), F3(~3, ~0x04, ~0)|ASI_RS2(~0),		"d,[1]", 0, v6 }, /* st d,[rs1+%g0] */
{ "st",	F3(3, 0x04, 1), F3(~3, ~0x04, ~1),			"d,[1+i]", 0, v6 },
{ "st",	F3(3, 0x04, 1), F3(~3, ~0x04, ~1),			"d,[i+1]", 0, v6 },
{ "st",	F3(3, 0x04, 1), F3(~3, ~0x04, ~1)|RS1_G0,		"d,[i]", 0, v6 },
{ "st",	F3(3, 0x04, 1), F3(~3, ~0x04, ~1)|SIMM13(~0),		"d,[1]", 0, v6 }, /* st d,[rs1+0] */
{ "st",	F3(3, 0x24, 0), F3(~3, ~0x24, ~0)|ASI(~0),		"g,[1+2]", 0, v6 },
{ "st",	F3(3, 0x24, 0), F3(~3, ~0x24, ~0)|ASI_RS2(~0),		"g,[1]", 0, v6 }, /* st d[rs1+%g0] */
{ "st",	F3(3, 0x24, 1), F3(~3, ~0x24, ~1),			"g,[1+i]", 0, v6 },
{ "st",	F3(3, 0x24, 1), F3(~3, ~0x24, ~1),			"g,[i+1]", 0, v6 },
{ "st",	F3(3, 0x24, 1), F3(~3, ~0x24, ~1)|RS1_G0,		"g,[i]", 0, v6 },
{ "st",	F3(3, 0x24, 1), F3(~3, ~0x24, ~1)|SIMM13(~0),		"g,[1]", 0, v6 }, /* st d,[rs1+0] */
{ "st",	F3(3, 0x34, 0), F3(~3, ~0x34, ~0)|ASI(~0),		"D,[1+2]", 0, v6 },
{ "st",	F3(3, 0x34, 0), F3(~3, ~0x34, ~0)|ASI_RS2(~0),		"D,[1]", 0, v6 }, /* st d,[rs1+%g0] */
{ "st",	F3(3, 0x34, 1), F3(~3, ~0x34, ~1),			"D,[1+i]", 0, v6 },
{ "st",	F3(3, 0x34, 1), F3(~3, ~0x34, ~1),			"D,[i+1]", 0, v6 },
{ "st",	F3(3, 0x34, 1), F3(~3, ~0x34, ~1)|RS1_G0,		"D,[i]", 0, v6 },
{ "st",	F3(3, 0x34, 1), F3(~3, ~0x34, ~1)|SIMM13(~0),		"D,[1]", 0, v6 }, /* st d,[rs1+0] */
{ "st",	F3(3, 0x35, 0), F3(~3, ~0x35, ~0)|ASI(~0),		"C,[1+2]", 0, v6 },
{ "st",	F3(3, 0x35, 0), F3(~3, ~0x35, ~0)|ASI_RS2(~0),		"C,[1]", 0, v6 }, /* st d,[rs1+%g0] */
{ "st",	F3(3, 0x35, 1), F3(~3, ~0x35, ~1),			"C,[1+i]", 0, v6 },
{ "st",	F3(3, 0x35, 1), F3(~3, ~0x35, ~1),			"C,[i+1]", 0, v6 },
{ "st",	F3(3, 0x35, 1), F3(~3, ~0x35, ~1)|RS1_G0,		"C,[i]", 0, v6 },
{ "st",	F3(3, 0x35, 1), F3(~3, ~0x35, ~1)|SIMM13(~0),		"C,[1]", 0, v6 }, /* st d,[rs1+0] */

{ "st",	F3(3, 0x25, 0), F3(~3, ~0x25, ~0)|RD_G0|ASI(~0),	"F,[1+2]", 0, v6 },
{ "st",	F3(3, 0x25, 0), F3(~3, ~0x25, ~0)|RD_G0|ASI_RS2(~0),	"F,[1]", 0, v6 }, /* st d,[rs1+%g0] */
{ "st",	F3(3, 0x25, 1), F3(~3, ~0x25, ~1)|RD_G0,		"F,[1+i]", 0, v6 },
{ "st",	F3(3, 0x25, 1), F3(~3, ~0x25, ~1)|RD_G0,		"F,[i+1]", 0, v6 },
{ "st",	F3(3, 0x25, 1), F3(~3, ~0x25, ~1)|RD_G0|RS1_G0,		"F,[i]", 0, v6 },
{ "st",	F3(3, 0x25, 1), F3(~3, ~0x25, ~1)|SIMM13(~0),		"F,[1]", 0, v6 }, /* st d,[rs1+0] */

 /* FIXME-v9: combine st, stw, stuw, stsw, in macros. */
{ "stw",	F3(3, 0x04, 0), F3(~3, ~0x04, ~0)|ASI(~0),		"d,[1+2]", F_ALIAS, v9 }, /* stw === st */
{ "stw",	F3(3, 0x04, 0), F3(~3, ~0x04, ~0)|ASI_RS2(~0),		"d,[1]", F_ALIAS, v9 }, /* st d,[rs1+%g0] */
{ "stw",	F3(3, 0x04, 1), F3(~3, ~0x04, ~1),			"d,[1+i]", F_ALIAS, v9 },
{ "stw",	F3(3, 0x04, 1), F3(~3, ~0x04, ~1),			"d,[i+1]", F_ALIAS, v9 },
{ "stw",	F3(3, 0x04, 1), F3(~3, ~0x04, ~1)|RS1_G0,		"d,[i]", F_ALIAS, v9 },
{ "stw",	F3(3, 0x04, 1), F3(~3, ~0x04, ~1)|SIMM13(~0),		"d,[1]", F_ALIAS, v9 }, /* st d,[rs1+0] */
{ "stw",	F3(3, 0x24, 0), F3(~3, ~0x24, ~0)|ASI(~0),		"g,[1+2]", F_ALIAS, v9 },
{ "stw",	F3(3, 0x24, 0), F3(~3, ~0x24, ~0)|ASI_RS2(~0),		"g,[1]", F_ALIAS, v9 }, /* st d[rs1+%g0] */
{ "stw",	F3(3, 0x24, 1), F3(~3, ~0x24, ~1),			"g,[1+i]", F_ALIAS, v9 },
{ "stw",	F3(3, 0x24, 1), F3(~3, ~0x24, ~1),			"g,[i+1]", F_ALIAS, v9 },
{ "stw",	F3(3, 0x24, 1), F3(~3, ~0x24, ~1)|RS1_G0,		"g,[i]", F_ALIAS, v9 },
{ "stw",	F3(3, 0x24, 1), F3(~3, ~0x24, ~1)|SIMM13(~0),		"g,[1]", F_ALIAS, v9 }, /* st d,[rs1+0] */
{ "stw",	F3(3, 0x34, 0), F3(~3, ~0x34, ~0)|ASI(~0),		"D,[1+2]", F_ALIAS, v9 },
{ "stw",	F3(3, 0x34, 0), F3(~3, ~0x34, ~0)|ASI_RS2(~0),		"D,[1]", F_ALIAS, v9 }, /* st d,[rs1+%g0] */
{ "stw",	F3(3, 0x34, 1), F3(~3, ~0x34, ~1),			"D,[1+i]", F_ALIAS, v9 },
{ "stw",	F3(3, 0x34, 1), F3(~3, ~0x34, ~1),			"D,[i+1]", F_ALIAS, v9 },
{ "stw",	F3(3, 0x34, 1), F3(~3, ~0x34, ~1)|RS1_G0,		"D,[i]", F_ALIAS, v9 },
{ "stw",	F3(3, 0x34, 1), F3(~3, ~0x34, ~1)|SIMM13(~0),		"D,[1]", F_ALIAS, v9 }, /* st d,[rs1+0] */
{ "stw",	F3(3, 0x35, 0), F3(~3, ~0x35, ~0)|ASI(~0),		"C,[1+2]", F_ALIAS, v9 },
{ "stw",	F3(3, 0x35, 0), F3(~3, ~0x35, ~0)|ASI_RS2(~0),		"C,[1]", F_ALIAS, v9 }, /* st d,[rs1+%g0] */
{ "stw",	F3(3, 0x35, 1), F3(~3, ~0x35, ~1),			"C,[1+i]", F_ALIAS, v9 },
{ "stw",	F3(3, 0x35, 1), F3(~3, ~0x35, ~1),			"C,[i+1]", F_ALIAS, v9 },
{ "stw",	F3(3, 0x35, 1), F3(~3, ~0x35, ~1)|RS1_G0,		"C,[i]", F_ALIAS, v9 },
{ "stw",	F3(3, 0x35, 1), F3(~3, ~0x35, ~1)|SIMM13(~0),		"C,[1]", F_ALIAS, v9 }, /* st d,[rs1+0] */
{ "stw",	F3(3, 0x25, 0), F3(~3, ~0x25, ~0)|RD_G0|ASI(~0),	"F,[1+2]", F_ALIAS, v9 },
{ "stw",	F3(3, 0x25, 0), F3(~3, ~0x25, ~0)|RD_G0|ASI_RS2(~0),	"F,[1]", F_ALIAS, v9 }, /* st d,[rs1+%g0] */
{ "stw",	F3(3, 0x25, 1), F3(~3, ~0x25, ~1)|RD_G0,		"F,[1+i]", F_ALIAS, v9 },
{ "stw",	F3(3, 0x25, 1), F3(~3, ~0x25, ~1)|RD_G0,		"F,[i+1]", F_ALIAS, v9 },
{ "stw",	F3(3, 0x25, 1), F3(~3, ~0x25, ~1)|RD_G0|RS1_G0,	"F,[i]", F_ALIAS, v9 },
{ "stw",	F3(3, 0x25, 1), F3(~3, ~0x25, ~1)|SIMM13(~0),		"F,[1]", F_ALIAS, v9 }, /* st d,[rs1+0] */

{ "stuw",	F3(3, 0x04, 0), F3(~3, ~0x04, ~0)|ASI(~0),		"d,[1+2]", F_ALIAS, v9 }, /* stuw === st */
{ "stuw",	F3(3, 0x04, 0), F3(~3, ~0x04, ~0)|ASI_RS2(~0),		"d,[1]", F_ALIAS, v9 }, /* st d,[rs1+%g0] */
{ "stuw",	F3(3, 0x04, 1), F3(~3, ~0x04, ~1),			"d,[1+i]", F_ALIAS, v9 },
{ "stuw",	F3(3, 0x04, 1), F3(~3, ~0x04, ~1),			"d,[i+1]", F_ALIAS, v9 },
{ "stuw",	F3(3, 0x04, 1), F3(~3, ~0x04, ~1)|RS1_G0,		"d,[i]", F_ALIAS, v9 },
{ "stuw",	F3(3, 0x04, 1), F3(~3, ~0x04, ~1)|SIMM13(~0),		"d,[1]", F_ALIAS, v9 }, /* st d,[rs1+0] */
{ "stuw",	F3(3, 0x24, 0), F3(~3, ~0x24, ~0)|ASI(~0),		"g,[1+2]", F_ALIAS, v9 },
{ "stuw",	F3(3, 0x24, 0), F3(~3, ~0x24, ~0)|ASI_RS2(~0),		"g,[1]", F_ALIAS, v9 }, /* st d[rs1+%g0] */
{ "stuw",	F3(3, 0x24, 1), F3(~3, ~0x24, ~1),			"g,[1+i]", F_ALIAS, v9 },
{ "stuw",	F3(3, 0x24, 1), F3(~3, ~0x24, ~1),			"g,[i+1]", F_ALIAS, v9 },
{ "stuw",	F3(3, 0x24, 1), F3(~3, ~0x24, ~1)|RS1_G0,		"g,[i]", F_ALIAS, v9 },
{ "stuw",	F3(3, 0x24, 1), F3(~3, ~0x24, ~1)|SIMM13(~0),		"g,[1]", F_ALIAS, v9 }, /* st d,[rs1+0] */
{ "stuw",	F3(3, 0x34, 0), F3(~3, ~0x34, ~0)|ASI(~0),		"D,[1+2]", F_ALIAS, v9 },
{ "stuw",	F3(3, 0x34, 0), F3(~3, ~0x34, ~0)|ASI_RS2(~0),		"D,[1]", F_ALIAS, v9 }, /* st d,[rs1+%g0] */
{ "stuw",	F3(3, 0x34, 1), F3(~3, ~0x34, ~1),			"D,[1+i]", F_ALIAS, v9 },
{ "stuw",	F3(3, 0x34, 1), F3(~3, ~0x34, ~1),			"D,[i+1]", F_ALIAS, v9 },
{ "stuw",	F3(3, 0x34, 1), F3(~3, ~0x34, ~1)|RS1_G0,		"D,[i]", F_ALIAS, v9 },
{ "stuw",	F3(3, 0x34, 1), F3(~3, ~0x34, ~1)|SIMM13(~0),		"D,[1]", F_ALIAS, v9 }, /* st d,[rs1+0] */
{ "stuw",	F3(3, 0x35, 0), F3(~3, ~0x35, ~0)|ASI(~0),		"C,[1+2]", F_ALIAS, v9 },
{ "stuw",	F3(3, 0x35, 0), F3(~3, ~0x35, ~0)|ASI_RS2(~0),		"C,[1]", F_ALIAS, v9 }, /* st d,[rs1+%g0] */
{ "stuw",	F3(3, 0x35, 1), F3(~3, ~0x35, ~1),			"C,[1+i]", F_ALIAS, v9 },
{ "stuw",	F3(3, 0x35, 1), F3(~3, ~0x35, ~1),			"C,[i+1]", F_ALIAS, v9 },
{ "stuw",	F3(3, 0x35, 1), F3(~3, ~0x35, ~1)|RS1_G0,		"C,[i]", F_ALIAS, v9 },
{ "stuw",	F3(3, 0x35, 1), F3(~3, ~0x35, ~1)|SIMM13(~0),		"C,[1]", F_ALIAS, v9 }, /* st d,[rs1+0] */
{ "stuw",	F3(3, 0x25, 0), F3(~3, ~0x25, ~0)|RD_G0|ASI(~0),	"F,[1+2]", F_ALIAS, v9 },
{ "stuw",	F3(3, 0x25, 0), F3(~3, ~0x25, ~0)|RD_G0|ASI_RS2(~0),	"F,[1]", F_ALIAS, v9 }, /* st d,[rs1+%g0] */
{ "stuw",	F3(3, 0x25, 1), F3(~3, ~0x25, ~1)|RD_G0,		"F,[1+i]", F_ALIAS, v9 },
{ "stuw",	F3(3, 0x25, 1), F3(~3, ~0x25, ~1)|RD_G0,		"F,[i+1]", F_ALIAS, v9 },
{ "stuw",	F3(3, 0x25, 1), F3(~3, ~0x25, ~1)|RD_G0|RS1_G0,	"F,[i]", F_ALIAS, v9 },
{ "stuw",	F3(3, 0x25, 1), F3(~3, ~0x25, ~1)|SIMM13(~0),		"F,[1]", F_ALIAS, v9 }, /* st d,[rs1+0] */

{ "stsw",	F3(3, 0x04, 0), F3(~3, ~0x04, ~0)|ASI(~0),		"d,[1+2]", F_ALIAS, v9 }, /* stsw === st */
{ "stsw",	F3(3, 0x04, 0), F3(~3, ~0x04, ~0)|ASI_RS2(~0),		"d,[1]", F_ALIAS, v9 }, /* st d,[rs1+%g0] */
{ "stsw",	F3(3, 0x04, 1), F3(~3, ~0x04, ~1),			"d,[1+i]", F_ALIAS, v9 },
{ "stsw",	F3(3, 0x04, 1), F3(~3, ~0x04, ~1),			"d,[i+1]", F_ALIAS, v9 },
{ "stsw",	F3(3, 0x04, 1), F3(~3, ~0x04, ~1)|RS1_G0,		"d,[i]", F_ALIAS, v9 },
{ "stsw",	F3(3, 0x04, 1), F3(~3, ~0x04, ~1)|SIMM13(~0),		"d,[1]", F_ALIAS, v9 }, /* st d,[rs1+0] */
{ "stsw",	F3(3, 0x24, 0), F3(~3, ~0x24, ~0)|ASI(~0),		"g,[1+2]", F_ALIAS, v9 },
{ "stsw",	F3(3, 0x24, 0), F3(~3, ~0x24, ~0)|ASI_RS2(~0),		"g,[1]", F_ALIAS, v9 }, /* st d[rs1+%g0] */
{ "stsw",	F3(3, 0x24, 1), F3(~3, ~0x24, ~1),			"g,[1+i]", F_ALIAS, v9 },
{ "stsw",	F3(3, 0x24, 1), F3(~3, ~0x24, ~1),			"g,[i+1]", F_ALIAS, v9 },
{ "stsw",	F3(3, 0x24, 1), F3(~3, ~0x24, ~1)|RS1_G0,		"g,[i]", F_ALIAS, v9 },
{ "stsw",	F3(3, 0x24, 1), F3(~3, ~0x24, ~1)|SIMM13(~0),		"g,[1]", F_ALIAS, v9 }, /* st d,[rs1+0] */
{ "stsw",	F3(3, 0x34, 0), F3(~3, ~0x34, ~0)|ASI(~0),		"D,[1+2]", F_ALIAS, v9 },
{ "stsw",	F3(3, 0x34, 0), F3(~3, ~0x34, ~0)|ASI_RS2(~0),		"D,[1]", F_ALIAS, v9 }, /* st d,[rs1+%g0] */
{ "stsw",	F3(3, 0x34, 1), F3(~3, ~0x34, ~1),			"D,[1+i]", F_ALIAS, v9 },
{ "stsw",	F3(3, 0x34, 1), F3(~3, ~0x34, ~1),			"D,[i+1]", F_ALIAS, v9 },
{ "stsw",	F3(3, 0x34, 1), F3(~3, ~0x34, ~1)|RS1_G0,		"D,[i]", F_ALIAS, v9 },
{ "stsw",	F3(3, 0x34, 1), F3(~3, ~0x34, ~1)|SIMM13(~0),		"D,[1]", F_ALIAS, v9 }, /* st d,[rs1+0] */
{ "stsw",	F3(3, 0x35, 0), F3(~3, ~0x35, ~0)|ASI(~0),		"C,[1+2]", F_ALIAS, v9 },
{ "stsw",	F3(3, 0x35, 0), F3(~3, ~0x35, ~0)|ASI_RS2(~0),		"C,[1]", F_ALIAS, v9 }, /* st d,[rs1+%g0] */
{ "stsw",	F3(3, 0x35, 1), F3(~3, ~0x35, ~1),			"C,[1+i]", F_ALIAS, v9 },
{ "stsw",	F3(3, 0x35, 1), F3(~3, ~0x35, ~1),			"C,[i+1]", F_ALIAS, v9 },
{ "stsw",	F3(3, 0x35, 1), F3(~3, ~0x35, ~1)|RS1_G0,		"C,[i]", F_ALIAS, v9 },
{ "stsw",	F3(3, 0x35, 1), F3(~3, ~0x35, ~1)|SIMM13(~0),		"C,[1]", F_ALIAS, v9 }, /* st d,[rs1+0] */
{ "stsw",	F3(3, 0x25, 0), F3(~3, ~0x25, ~0)|RD_G0|ASI(~0),	"F,[1+2]", F_ALIAS, v9 },
{ "stsw",	F3(3, 0x25, 0), F3(~3, ~0x25, ~0)|RD_G0|ASI_RS2(~0),	"F,[1]", F_ALIAS, v9 }, /* st d,[rs1+%g0] */
{ "stsw",	F3(3, 0x25, 1), F3(~3, ~0x25, ~1)|RD_G0,		"F,[1+i]", F_ALIAS, v9 },
{ "stsw",	F3(3, 0x25, 1), F3(~3, ~0x25, ~1)|RD_G0,		"F,[i+1]", F_ALIAS, v9 },
{ "stsw",	F3(3, 0x25, 1), F3(~3, ~0x25, ~1)|RD_G0|RS1_G0,	"F,[i]", F_ALIAS, v9 },
{ "stsw",	F3(3, 0x25, 1), F3(~3, ~0x25, ~1)|SIMM13(~0),		"F,[1]", F_ALIAS, v9 }, /* st d,[rs1+0] */

{ "sta",	F3(3, 0x14, 0), F3(~3, ~0x14, ~0),		"d,[1+2]A", 0, v6 },
{ "sta",	F3(3, 0x14, 0), F3(~3, ~0x14, ~0)|RS2(~0),	"d,[1]A", 0, v6 }, /* sta d,[rs1+%g0] */

{ "stwa",	F3(3, 0x14, 0), F3(~3, ~0x14, ~0),		"d,[1+2]A", F_ALIAS, v9 },
{ "stwa",	F3(3, 0x14, 0), F3(~3, ~0x14, ~0)|RS2(~0),	"d,[1]A", F_ALIAS, v9 }, /* sta d,[rs1+%g0] */

{ "stswa",	F3(3, 0x14, 0), F3(~3, ~0x14, ~0),		"d,[1+2]A", F_ALIAS, v9 },
{ "stswa",	F3(3, 0x14, 0), F3(~3, ~0x14, ~0)|RS2(~0),	"d,[1]A", F_ALIAS, v9 }, /* sta d,[rs1+%g0] */

{ "stuwa",	F3(3, 0x14, 0), F3(~3, ~0x14, ~0),		"d,[1+2]A", F_ALIAS, v9 },
{ "stuwa",	F3(3, 0x14, 0), F3(~3, ~0x14, ~0)|RS2(~0),	"d,[1]A", F_ALIAS, v9 }, /* sta d,[rs1+%g0] */

{ "stb",	F3(3, 0x05, 0), F3(~3, ~0x05, ~0)|ASI(~0),	"d,[1+2]", 0, v6 },
{ "stb",	F3(3, 0x05, 0), F3(~3, ~0x05, ~0)|ASI_RS2(~0),	"d,[1]", 0, v6 }, /* stb d,[rs1+%g0] */
{ "stb",	F3(3, 0x05, 1), F3(~3, ~0x05, ~1),		"d,[1+i]", 0, v6 },
{ "stb",	F3(3, 0x05, 1), F3(~3, ~0x05, ~1),		"d,[i+1]", 0, v6 },
{ "stb",	F3(3, 0x05, 1), F3(~3, ~0x05, ~1)|RS1_G0,	"d,[i]", 0, v6 },
{ "stb",	F3(3, 0x05, 1), F3(~3, ~0x05, ~1)|SIMM13(~0),	"d,[1]", 0, v6 }, /* stb d,[rs1+0] */

{ "stub",	F3(3, 0x05, 0), F3(~3, ~0x05, ~0)|ASI(~0),	"d,[1+2]", F_ALIAS, v9 },
{ "stub",	F3(3, 0x05, 0), F3(~3, ~0x05, ~0)|ASI_RS2(~0),	"d,[1]", F_ALIAS, v9 }, /* stb d,[rs1+%g0] */
{ "stub",	F3(3, 0x05, 1), F3(~3, ~0x05, ~1),		"d,[1+i]", F_ALIAS, v9 },
{ "stub",	F3(3, 0x05, 1), F3(~3, ~0x05, ~1),		"d,[i+1]", F_ALIAS, v9 },
{ "stub",	F3(3, 0x05, 1), F3(~3, ~0x05, ~1)|RS1_G0,	"d,[i]", F_ALIAS, v9 },
{ "stub",	F3(3, 0x05, 1), F3(~3, ~0x05, ~1)|SIMM13(~0),	"d,[1]", F_ALIAS, v9 }, /* stb d,[rs1+0] */

{ "stsb",	F3(3, 0x05, 0), F3(~3, ~0x05, ~0)|ASI(~0),	"d,[1+2]", F_ALIAS, v9 },
{ "stsb",	F3(3, 0x05, 0), F3(~3, ~0x05, ~0)|ASI_RS2(~0),	"d,[1]", F_ALIAS, v9 }, /* stb d,[rs1+%g0] */
{ "stsb",	F3(3, 0x05, 1), F3(~3, ~0x05, ~1),		"d,[1+i]", F_ALIAS, v9 },
{ "stsb",	F3(3, 0x05, 1), F3(~3, ~0x05, ~1),		"d,[i+1]", F_ALIAS, v9 },
{ "stsb",	F3(3, 0x05, 1), F3(~3, ~0x05, ~1)|RS1_G0,	"d,[i]", F_ALIAS, v9 },
{ "stsb",	F3(3, 0x05, 1), F3(~3, ~0x05, ~1)|SIMM13(~0),	"d,[1]", F_ALIAS, v9 }, /* stb d,[rs1+0] */

{ "stba",	F3(3, 0x15, 0), F3(~3, ~0x15, ~0),		"d,[1+2]A", 0, v6 },
{ "stba",	F3(3, 0x15, 0), F3(~3, ~0x15, ~0)|RS2(~0),	"d,[1]A", 0, v6 }, /* stba d,[rs1+%g0] */

{ "stsba",	F3(3, 0x15, 0), F3(~3, ~0x15, ~0),		"d,[1+2]A", F_ALIAS, v9 },
{ "stsba",	F3(3, 0x15, 0), F3(~3, ~0x15, ~0)|RS2(~0),	"d,[1]A", F_ALIAS, v9 }, /* stba d,[rs1+%g0] */

{ "stuba",	F3(3, 0x15, 0), F3(~3, ~0x15, ~0),		"d,[1+2]A", F_ALIAS, v9 },
{ "stuba",	F3(3, 0x15, 0), F3(~3, ~0x15, ~0)|RS2(~0),	"d,[1]A", F_ALIAS, v9 }, /* stba d,[rs1+%g0] */

{ "std",	F3(3, 0x07, 0), F3(~3, ~0x07, ~0)|ASI(~0),	"d,[1+2]", 0, v6 },
{ "std",	F3(3, 0x07, 0), F3(~3, ~0x07, ~0)|ASI_RS2(~0),	"d,[1]", 0, v6 }, /* std d,[rs1+%g0] */
{ "std",	F3(3, 0x07, 1), F3(~3, ~0x07, ~1),		"d,[1+i]", 0, v6 },
{ "std",	F3(3, 0x07, 1), F3(~3, ~0x07, ~1),		"d,[i+1]", 0, v6 },
{ "std",	F3(3, 0x07, 1), F3(~3, ~0x07, ~1)|RS1_G0,	"d,[i]", 0, v6 },
{ "std",	F3(3, 0x07, 1), F3(~3, ~0x07, ~1)|SIMM13(~0),	"d,[1]", 0, v6 }, /* std d,[rs1+0] */
{ "std",	F3(3, 0x26, 0), F3(~3, ~0x26, ~0)|ASI(~0),	"q,[1+2]", 0, v6 },
{ "std",	F3(3, 0x26, 0), F3(~3, ~0x26, ~0)|ASI_RS2(~0),	"q,[1]", 0, v6 }, /* std d,[rs1+%g0] */
{ "std",	F3(3, 0x26, 1), F3(~3, ~0x26, ~1),		"q,[1+i]", 0, v6 },
{ "std",	F3(3, 0x26, 1), F3(~3, ~0x26, ~1),		"q,[i+1]", 0, v6 },
{ "std",	F3(3, 0x26, 1), F3(~3, ~0x26, ~1)|RS1_G0,	"q,[i]", 0, v6 },
{ "std",	F3(3, 0x26, 1), F3(~3, ~0x26, ~1)|SIMM13(~0),	"q,[1]", 0, v6 }, /* std d,[rs1+0] */
{ "std",	F3(3, 0x27, 0), F3(~3, ~0x27, ~0)|ASI(~0),	"g,[1+2]", 0, v6 },
{ "std",	F3(3, 0x27, 0), F3(~3, ~0x27, ~0)|ASI_RS2(~0),	"g,[1]", 0, v6 }, /* std d,[rs1+%g0] */
{ "std",	F3(3, 0x27, 1), F3(~3, ~0x27, ~1),		"g,[1+i]", 0, v6 },
{ "std",	F3(3, 0x27, 1), F3(~3, ~0x27, ~1),		"g,[i+1]", 0, v6 },
{ "std",	F3(3, 0x27, 1), F3(~3, ~0x27, ~1)|RS1_G0,	"g,[i]", 0, v6 },
{ "std",	F3(3, 0x27, 1), F3(~3, ~0x27, ~1)|SIMM13(~0),	"g,[1]", 0, v6 }, /* std d,[rs1+0] */
{ "std",	F3(3, 0x36, 0), F3(~3, ~0x36, ~0)|ASI(~0),	"Q,[1+2]", 0, v6 },
{ "std",	F3(3, 0x36, 0), F3(~3, ~0x36, ~0)|ASI_RS2(~0),	"Q,[1]", 0, v6 }, /* std d,[rs1+%g0] */
{ "std",	F3(3, 0x36, 1), F3(~3, ~0x36, ~1),		"Q,[1+i]", 0, v6 },
{ "std",	F3(3, 0x36, 1), F3(~3, ~0x36, ~1),		"Q,[i+1]", 0, v6 },
{ "std",	F3(3, 0x36, 1), F3(~3, ~0x36, ~1)|RS1_G0,	"Q,[i]", 0, v6 },
{ "std",	F3(3, 0x36, 1), F3(~3, ~0x36, ~1)|SIMM13(~0),	"Q,[1]", 0, v6 }, /* std d,[rs1+0] */
{ "std",	F3(3, 0x37, 0), F3(~3, ~0x37, ~0)|ASI(~0),	"D,[1+2]", 0, v6 },
{ "std",	F3(3, 0x37, 0), F3(~3, ~0x37, ~0)|ASI_RS2(~0),	"D,[1]", 0, v6 }, /* std d,[rs1+%g0] */
{ "std",	F3(3, 0x37, 1), F3(~3, ~0x37, ~1),		"D,[1+i]", 0, v6 },
{ "std",	F3(3, 0x37, 1), F3(~3, ~0x37, ~1),		"D,[i+1]", 0, v6 },
{ "std",	F3(3, 0x37, 1), F3(~3, ~0x37, ~1)|RS1_G0,	"D,[i]", 0, v6 },
{ "std",	F3(3, 0x37, 1), F3(~3, ~0x37, ~1)|SIMM13(~0),	"D,[1]", 0, v6 }, /* std d,[rs1+0] */

{ "stda",	F3(3, 0x17, 0), F3(~3, ~0x17, ~0),		"d,[1+2]A", 0, v6 },
{ "stda",	F3(3, 0x17, 0), F3(~3, ~0x17, ~0)|RS2(~0),	"d,[1]A", 0, v6 }, /* stda d,[rs1+%g0] */

{ "sth",	F3(3, 0x06, 0), F3(~3, ~0x06, ~0)|ASI(~0),	"d,[1+2]", 0, v6 },
{ "sth",	F3(3, 0x06, 0), F3(~3, ~0x06, ~0)|ASI_RS2(~0),	"d,[1]", 0, v6 }, /* sth d,[rs1+%g0] */
{ "sth",	F3(3, 0x06, 1), F3(~3, ~0x06, ~1),		"d,[1+i]", 0, v6 },
{ "sth",	F3(3, 0x06, 1), F3(~3, ~0x06, ~1),		"d,[i+1]", 0, v6 },
{ "sth",	F3(3, 0x06, 1), F3(~3, ~0x06, ~1)|RS1_G0,	"d,[i]", 0, v6 },
{ "sth",	F3(3, 0x06, 1), F3(~3, ~0x06, ~1)|SIMM13(~0),	"d,[1]", 0, v6 }, /* sth d,[+] */

{ "stsh",	F3(3, 0x06, 0), F3(~3, ~0x06, ~0)|ASI(~0),	"d,[1+2]", F_ALIAS, v9 },
{ "stsh",	F3(3, 0x06, 0), F3(~3, ~0x06, ~0)|ASI_RS2(~0),	"d,[1]", F_ALIAS, v9 }, /* sth d,[rs1+%g0] */
{ "stsh",	F3(3, 0x06, 1), F3(~3, ~0x06, ~1),		"d,[1+i]", F_ALIAS, v9 },
{ "stsh",	F3(3, 0x06, 1), F3(~3, ~0x06, ~1),		"d,[i+1]", F_ALIAS, v9 },
{ "stsh",	F3(3, 0x06, 1), F3(~3, ~0x06, ~1)|RS1_G0,	"d,[i]", F_ALIAS, v9 },
{ "stsh",	F3(3, 0x06, 1), F3(~3, ~0x06, ~1)|SIMM13(~0),	"d,[1]", F_ALIAS, v9 }, /* sth d,[rs1+0] */

{ "stuh",	F3(3, 0x06, 0), F3(~3, ~0x06, ~0)|ASI(~0),	"d,[1+2]", F_ALIAS, v9 },
{ "stuh",	F3(3, 0x06, 0), F3(~3, ~0x06, ~0)|ASI_RS2(~0),	"d,[1]", F_ALIAS, v9 }, /* sth d,[rs1+%g0] */
{ "stuh",	F3(3, 0x06, 1), F3(~3, ~0x06, ~1),		"d,[1+i]", F_ALIAS, v9 },
{ "stuh",	F3(3, 0x06, 1), F3(~3, ~0x06, ~1),		"d,[i+1]", F_ALIAS, v9 },
{ "stuh",	F3(3, 0x06, 1), F3(~3, ~0x06, ~1)|RS1_G0,	"d,[i]", F_ALIAS, v9 },
{ "stuh",	F3(3, 0x06, 1), F3(~3, ~0x06, ~1)|SIMM13(~0),	"d,[1]", F_ALIAS, v9 }, /* sth d,[rs1+0] */

{ "stha",	F3(3, 0x16, 0), F3(~3, ~0x16, ~0),		"d,[1+2]A", 0, v6 },
{ "stha",	F3(3, 0x16, 0), F3(~3, ~0x16, ~0)|RS2(~0),	"d,[1]A", 0, v6 }, /* stha ,[+%] */

{ "stsha",	F3(3, 0x16, 0), F3(~3, ~0x16, ~0),		"d,[1+2]A", F_ALIAS, v9 },
{ "stsha",	F3(3, 0x16, 0), F3(~3, ~0x16, ~0)|RS2(~0),	"d,[1]A", F_ALIAS, v9 }, /* stha d,[rs1+%g0] */

{ "stuha",	F3(3, 0x16, 0), F3(~3, ~0x16, ~0),		"d,[1+2]A", F_ALIAS, v9 },
{ "stuha",	F3(3, 0x16, 0), F3(~3, ~0x16, ~0)|RS2(~0),	"d,[1]A", F_ALIAS, v9 }, /* stha d,[rs1+%g0] */

{ "stx",	F3(3, 0x0e, 0), F3(~3, ~0x0e, ~0)|ASI(~0),		"d,[1+2]", 0, v9 },
{ "stx",	F3(3, 0x0e, 0), F3(~3, ~0x0e, ~0)|ASI_RS2(~0),		"d,[1]", 0, v9 }, /* stx d,[rs1+%g0] */
{ "stx",	F3(3, 0x0e, 1), F3(~3, ~0x0e, ~1),			"d,[1+i]", 0, v9 },
{ "stx",	F3(3, 0x0e, 1), F3(~3, ~0x0e, ~1),			"d,[i+1]", 0, v9 },
{ "stx",	F3(3, 0x0e, 1), F3(~3, ~0x0e, ~1)|RS1_G0,		"d,[i]", 0, v9 },
{ "stx",	F3(3, 0x0e, 1), F3(~3, ~0x0e, ~1)|SIMM13(~0),		"d,[1]", 0, v9 }, /* stx d,[rs1+0] */
{ "stx",	F3(3, 0x2d, 0), F3(~3, ~0x2d, ~0)|RD_G0|ASI(~0),	"F,[1+2]", F_ALIAS, v9 },
{ "stx",	F3(3, 0x2d, 0), F3(~3, ~0x2d, ~0)|RD_G0|ASI_RS2(~0),	"F,[1]", F_ALIAS, v9 }, /* st d,[rs1+%g0] */
{ "stx",	F3(3, 0x2d, 1), F3(~3, ~0x2d, ~1)|RD_G0,		"F,[1+i]", F_ALIAS, v9 },
{ "stx",	F3(3, 0x2d, 1), F3(~3, ~0x2d, ~1)|RD_G0,		"F,[i+1]", F_ALIAS, v9 },
{ "stx",	F3(3, 0x2d, 1), F3(~3, ~0x2d, ~1)|RD_G0|RS1_G0,		"F,[i]", F_ALIAS, v9 },
{ "stx",	F3(3, 0x2d, 1), F3(~3, ~0x2d, ~1)|SIMM13(~0),		"F,[1]", F_ALIAS, v9 }, /* st d,[rs1+0] */

{ "stxa",	F3(3, 0x1e, 0), F3(~3, ~0x1e, ~0),		"d,[1+2]A", 0, v9 },
{ "stxa",	F3(3, 0x1e, 0), F3(~3, ~0x1e, ~0)|RS2(~0),	"d,[1]A", 0, v9 }, /* stha d,[rs1+%g0] */

{ "swap",	F3(3, 0x0f, 0), F3(~3, ~0x0f, ~0)|ASI(~0),	"[1+2],d", 0, v7 },
{ "swap",	F3(3, 0x0f, 0), F3(~3, ~0x0f, ~0)|ASI_RS2(~0),	"[1],d", 0, v7 }, /* swap [rs1+%g0],d */
{ "swap",	F3(3, 0x0f, 1), F3(~3, ~0x0f, ~1),		"[1+i],d", 0, v7 },
{ "swap",	F3(3, 0x0f, 1), F3(~3, ~0x0f, ~1),		"[i+1],d", 0, v7 },
{ "swap",	F3(3, 0x0f, 1), F3(~3, ~0x0f, ~1)|RS1_G0,	"[i],d", 0, v7 },
{ "swap",	F3(3, 0x0f, 1), F3(~3, ~0x0f, ~1)|SIMM13(~0),	"[1],d", 0, v7 }, /* swap [rs1+0],d */

{ "swapa",	F3(3, 0x1f, 0), F3(~3, ~0x1f, ~0),		"[1+2]A,d", 0, v7 },
{ "swapa",	F3(3, 0x1f, 0), F3(~3, ~0x1f, ~0)|RS2(~0),	"[1]A,d", 0, v7 }, /* swapa [rs1+%g0],d */

{ "restore",	F3(2, 0x3d, 0), F3(~2, ~0x3d, ~0)|ASI(~0),			"1,2,d", 0, v6 },
{ "restore",	F3(2, 0x3d, 0), F3(~2, ~0x3d, ~0)|RD_G0|RS1_G0|ASI_RS2(~0),	"", 0, v6 }, /* restore %g0,%g0,%g0 */
{ "restore",	F3(2, 0x3d, 1), F3(~2, ~0x3d, ~1),				"1,i,d", 0, v6 },
{ "restore",	F3(2, 0x3d, 1), F3(~2, ~0x3d, ~1)|RD_G0|RS1_G0|SIMM13(~0),	"", 0, v6 }, /* restore %g0,0,%g0 */

{ "rett",	F3(2, 0x39, 0), F3(~2, ~0x39, ~0)|RD_G0|ASI(~0),	"1+2", F_DELAYED, v6 }, /* rett rs1+rs2 */
{ "rett",	F3(2, 0x39, 0), F3(~2, ~0x39, ~0)|RD_G0|ASI_RS2(~0),	"1", F_DELAYED, v6 },	/* rett rs1,%g0 */
{ "rett",	F3(2, 0x39, 1), F3(~2, ~0x39, ~1)|RD_G0,	"1+i", F_DELAYED, v6 }, /* rett rs1+X */
{ "rett",	F3(2, 0x39, 1), F3(~2, ~0x39, ~1)|RD_G0,	"i+1", F_DELAYED, v6 }, /* rett X+rs1 */
{ "rett",	F3(2, 0x39, 1), F3(~2, ~0x39, ~1)|RD_G0|RS1_G0,"i", F_DELAYED, v6 }, /* rett X+rs1 */
{ "rett",	F3(2, 0x39, 1), F3(~2, ~0x39, ~1)|RD_G0|RS1_G0,	"i", F_DELAYED, v6 },	/* rett X */
{ "rett",	F3(2, 0x39, 1), F3(~2, ~0x39, ~1)|RD_G0|SIMM13(~0),	"1", F_DELAYED, v6 },	/* rett rs1+0 */

{ "save",	F3(2, 0x3c, 0), F3(~2, ~0x3c, ~0)|ASI(~0),	"1,2,d", 0, v6 },
{ "save",	F3(2, 0x3c, 1), F3(~2, ~0x3c, ~1),		"1,i,d", 0, v6 },

{ "ret",  F3(2, 0x38, 1)|RS1(0x1f)|SIMM13(8), F3(~2, ~0x38, ~1)|SIMM13(~8),	       "", F_DELAYED, v6 }, /* jmpl %i7+8,%g0 */
{ "retl", F3(2, 0x38, 1)|RS1(0x0f)|SIMM13(8), F3(~2, ~0x38, ~1)|RS1(~0x0f)|SIMM13(~8), "", F_DELAYED, v6 }, /* jmpl %o7+8,%g0 */

{ "jmpl",	F3(2, 0x38, 0), F3(~2, ~0x38, ~0)|ASI(~0),	"1+2,d", F_DELAYED, v6 },
{ "jmpl",	F3(2, 0x38, 0), F3(~2, ~0x38, ~0)|ASI_RS2(~0),	"1,d", F_DELAYED, v6 }, /* jmpl rs1+%g0,d */
{ "jmpl",	F3(2, 0x38, 1), F3(~2, ~0x38, ~1)|SIMM13(~0),	"1,d", F_DELAYED, v6 }, /* jmpl rs1+0,d */
{ "jmpl",	F3(2, 0x38, 1), F3(~2, ~0x38, ~1)|RS1_G0,	"i,d", F_DELAYED, v6 }, /* jmpl %g0+i,d */
{ "jmpl",	F3(2, 0x38, 1), F3(~2, ~0x38, ~1),		"1+i,d", F_DELAYED, v6 },
{ "jmpl",	F3(2, 0x38, 1), F3(~2, ~0x38, ~1),		"i+1,d", F_DELAYED, v6 },
{ "jmpl",	F3(2, 0x38, 1), F3(~2, ~0x38, ~1)|RS1_G0,	"i,d", F_DELAYED, v6 },

 /* The 1<<12 is a long story.  It is necessary.  For more info, please contact rich@cygnus.com */
{ "sll",	F3(2, 0x25, 0), F3(~2, ~0x25, ~0)|(1<<12)|ASI(~0),	"1,2,d", 0, v6 },
{ "sll",	F3(2, 0x25, 1), F3(~2, ~0x25, ~1)|(1<<12),		"1,i,d", 0, v6 },
{ "sra",	F3(2, 0x27, 0), F3(~2, ~0x27, ~0)|(1<<12)|ASI(~0),	"1,2,d", 0, v6 },
{ "sra",	F3(2, 0x27, 1), F3(~2, ~0x27, ~1)|(1<<12),		"1,i,d", 0, v6 },
{ "srl",	F3(2, 0x26, 0), F3(~2, ~0x26, ~0)|(1<<12)|ASI(~0),	"1,2,d", 0, v6 },
{ "srl",	F3(2, 0x26, 1), F3(~2, ~0x26, ~1)|(1<<12),		"1,i,d", 0, v6 },

{ "sllw",	F3(2, 0x25, 0), F3(~2, ~0x25, ~0)|(1<<12)|ASI(~0),	"1,2,d", F_ALIAS, v9 },	/* sllw === sll */
{ "sllw",	F3(2, 0x25, 1), F3(~2, ~0x25, ~1)|(1<<12),		"1,i,d", F_ALIAS, v9 },
{ "sraw",	F3(2, 0x27, 0), F3(~2, ~0x27, ~0)|(1<<12)|ASI(~0),	"1,2,d", F_ALIAS, v9 },	/* sraw === sra */
{ "sraw",	F3(2, 0x27, 1), F3(~2, ~0x27, ~1)|(1<<12),		"1,i,d", F_ALIAS, v9 },
{ "srlw",	F3(2, 0x26, 0), F3(~2, ~0x26, ~0)|(1<<12)|ASI(~0),	"1,2,d", F_ALIAS, v9 },	/* srlw === srl */
{ "srlw",	F3(2, 0x26, 1), F3(~2, ~0x26, ~1)|(1<<12),		"1,i,d", F_ALIAS, v9 },

{ "sllx",	F3(2, 0x25, 0)|(1<<12), F3(~2, ~0x25, ~0)|(ASI(~0)^(1<<12)),	"1,2,d", 0, v9 },
{ "sllx",	F3(2, 0x25, 1)|(1<<12), F3(~2, ~0x25, ~1),		"1,i,d", 0, v9 },
{ "srax",	F3(2, 0x27, 0)|(1<<12), F3(~2, ~0x27, ~0)|(ASI(~0)^(1<<12)),	"1,2,d", 0, v9 },
{ "srax",	F3(2, 0x27, 1)|(1<<12), F3(~2, ~0x27, ~1),		"1,i,d", 0, v9 },
{ "srlx",	F3(2, 0x26, 0)|(1<<12), F3(~2, ~0x26, ~0)|(ASI(~0)^(1<<12)),	"1,2,d", 0, v9 },
{ "srlx",	F3(2, 0x26, 1)|(1<<12), F3(~2, ~0x26, ~1),		"1,i,d", 0, v9 },

{ "mulscc",	F3(2, 0x24, 0), F3(~2, ~0x24, ~0)|ASI(~0),	"1,2,d", 0, v6 },
{ "mulscc",	F3(2, 0x24, 1), F3(~2, ~0x24, ~1),		"1,i,d", 0, v6 },

{ "clr",	F3(2, 0x02, 0), F3(~2, ~0x02, ~0)|RD_G0|RS1_G0|ASI_RS2(~0),	"d", F_ALIAS, v6 }, /* or %g0,%g0,d */
{ "clr",	F3(2, 0x02, 1), F3(~2, ~0x02, ~1)|RS1_G0|SIMM13(~0),		"d", F_ALIAS, v6 }, /* or %g0,0,d	*/
{ "clr",	F3(3, 0x04, 0), F3(~3, ~0x04, ~0)|RD_G0|ASI(~0),		"[1+2]", F_ALIAS, v6 },
{ "clr",	F3(3, 0x04, 0), F3(~3, ~0x04, ~0)|RD_G0|ASI_RS2(~0),		"[1]", F_ALIAS, v6 }, /* st %g0,[rs1+%g0] */
{ "clr",	F3(3, 0x04, 1), F3(~3, ~0x04, ~1)|RD_G0,			"[1+i]", F_ALIAS, v6 },
{ "clr",	F3(3, 0x04, 1), F3(~3, ~0x04, ~1)|RD_G0,			"[i+1]", F_ALIAS, v6 },
{ "clr",	F3(3, 0x04, 1), F3(~3, ~0x04, ~1)|RD_G0|RS1_G0,		"[i]", F_ALIAS, v6 },
{ "clr",	F3(3, 0x04, 1), F3(~3, ~0x04, ~1)|RD_G0|SIMM13(~0),		"[1]", F_ALIAS, v6 }, /* st %g0,[rs1+0] */

{ "clrb",	F3(3, 0x05, 0), F3(~3, ~0x05, ~0)|RD_G0|ASI(~0),	"[1+2]", F_ALIAS, v6 },
{ "clrb",	F3(3, 0x05, 0), F3(~3, ~0x05, ~0)|RD_G0|ASI_RS2(~0),	"[1]", F_ALIAS, v6 }, /* stb %g0,[rs1+%g0] */
{ "clrb",	F3(3, 0x05, 1), F3(~3, ~0x05, ~1)|RD_G0,		"[1+i]", F_ALIAS, v6 },
{ "clrb",	F3(3, 0x05, 1), F3(~3, ~0x05, ~1)|RD_G0,		"[i+1]", F_ALIAS, v6 },
{ "clrb",	F3(3, 0x05, 1), F3(~3, ~0x05, ~1)|RD_G0|RS1_G0,	"[i]", F_ALIAS, v6 },

{ "clrh",	F3(3, 0x06, 0), F3(~3, ~0x06, ~0)|RD_G0|ASI(~0),	"[1+2]", F_ALIAS, v6 },
{ "clrh",	F3(3, 0x06, 0), F3(~3, ~0x06, ~0)|RD_G0|ASI_RS2(~0),	"[1]", F_ALIAS, v6 }, /* sth %g0,[rs1+%g0] */
{ "clrh",	F3(3, 0x06, 1), F3(~3, ~0x06, ~1)|RD_G0,		"[1+i]", F_ALIAS, v6 },
{ "clrh",	F3(3, 0x06, 1), F3(~3, ~0x06, ~1)|RD_G0,		"[i+1]", F_ALIAS, v6 },
{ "clrh",	F3(3, 0x06, 1), F3(~3, ~0x06, ~1)|RD_G0|RS1_G0,	"[i]", F_ALIAS, v6 },

{ "orcc",	F3(2, 0x12, 0), F3(~2, ~0x12, ~0)|ASI(~0),	"1,2,d", 0, v6 },
{ "orcc",	F3(2, 0x12, 1), F3(~2, ~0x12, ~1),		"1,i,d", 0, v6 },
{ "orcc",	F3(2, 0x12, 1), F3(~2, ~0x12, ~1),		"i,1,d", 0, v6 },

{ "orncc",	F3(2, 0x16, 0), F3(~2, ~0x16, ~0)|ASI(~0),	"1,2,d", 0, v6 },
{ "orncc",	F3(2, 0x16, 1), F3(~2, ~0x16, ~1),		"1,i,d", 0, v6 },
{ "orncc",	F3(2, 0x16, 1), F3(~2, ~0x16, ~1),		"i,1,d", 0, v6 },

{ "orn",	F3(2, 0x06, 0), F3(~2, ~0x06, ~0)|ASI(~0),	"1,2,d", 0, v6 },
{ "orn",	F3(2, 0x06, 1), F3(~2, ~0x06, ~1),		"1,i,d", 0, v6 },
{ "orn",	F3(2, 0x06, 1), F3(~2, ~0x06, ~1),		"i,1,d", 0, v6 },

{ "tst",	F3(2, 0x12, 0), F3(~2, ~0x12, ~0)|RD_G0|ASI_RS2(~0),	"1", 0, v6 }, /* orcc rs1, %g0, %g0 */
{ "tst",	F3(2, 0x12, 0), F3(~2, ~0x12, ~0)|RD_G0|RS1_G0|ASI(~0),	"2", 0, v6 }, /* orcc %g0, rs2, %g0 */
{ "tst",	F3(2, 0x12, 1), F3(~2, ~0x12, ~1)|RD_G0|SIMM13(~0),	"1", 0, v6 }, /* orcc rs1, 0, %g0 */

{ "wr",	F3(2, 0x30, 0),		F3(~2, ~0x30, ~0)|ASI(~0),		"1,2,m", 0, v8 }, /* wr r,r,%asrX */
{ "wr",	F3(2, 0x30, 0),		F3(~2, ~0x30, ~0)|RD_G0|ASI(~0),	"1,2,y", 0, v6 }, /* wr r,r,%y */
{ "wr",	F3(2, 0x30, 1),		F3(~2, ~0x30, ~1),			"1,i,m", 0, v8 }, /* wr r,i,%asrX */
{ "wr",	F3(2, 0x30, 1),		F3(~2, ~0x30, ~1)|RD_G0,		"1,i,y", 0, v6 }, /* wr r,i,%y */
{ "wr",	F3(2, 0x31, 0),		F3(~2, ~0x31, ~0)|RD_G0|ASI(~0),	"1,2,p", 0, v6 }, /* wr r,r,%psr */
{ "wr",	F3(2, 0x31, 1),		F3(~2, ~0x31, ~1)|RD_G0,		"1,i,p", 0, v6 }, /* wr r,i,%psr */
{ "wr",	F3(2, 0x32, 0),		F3(~2, ~0x32, ~0)|RD_G0|ASI(~0),	"1,2,w", 0, v6 }, /* wr r,r,%wim */
{ "wr",	F3(2, 0x32, 1),		F3(~2, ~0x32, ~1)|RD_G0,		"1,i,w", 0, v6 }, /* wr r,i,%wim */
{ "wr",	F3(2, 0x33, 0),		F3(~2, ~0x33, ~0)|RD_G0|ASI(~0),	"1,2,t", 0, v6 }, /* wr r,r,%tbr */
{ "wr",	F3(2, 0x33, 1),		F3(~2, ~0x33, ~1)|RD_G0,		"1,i,t", 0, v6 }, /* wr r,i,%tbr */

{ "wr", F3(2, 0x30, 0)|RD(0), F3(~2, ~0x30, ~0)|RD(~0)|ASI(~0), "1,2,y", 0, v9 },
{ "wr", F3(2, 0x30, 1)|RD(0), F3(~2, ~0x30, ~1)|RD(~0),		"1,i,y", 0, v9 },
{ "wr", F3(2, 0x30, 0)|RD(1), F3(~2, ~0x30, ~0)|RD(~1)|ASI(~0), "1,2,E", 0, v9 },
{ "wr", F3(2, 0x30, 1)|RD(1), F3(~2, ~0x30, ~1)|RD(~1),		"1,i,E", 0, v9 },
{ "wr", F3(2, 0x30, 0)|RD(3), F3(~2, ~0x30, ~0)|RD(~3)|ASI(~0), "1,2,W", 0, v9 },
{ "wr", F3(2, 0x30, 1)|RD(3), F3(~2, ~0x30, ~1)|RD(~3),		"1,i,W", 0, v9 },
{ "wr", F3(2, 0x30, 0)|RD(4), F3(~2, ~0x30, ~0)|RD(~4)|ASI(~0), "1,2,p", 0, v9 },
{ "wr", F3(2, 0x30, 1)|RD(4), F3(~2, ~0x30, ~1)|RD(~4),		"1,i,p", 0, v9 },
{ "wr", F3(2, 0x30, 0)|RD(5), F3(~2, ~0x30, ~0)|RD(~5)|ASI(~0), "1,2,w", 0, v9 },
{ "wr", F3(2, 0x30, 1)|RD(5), F3(~2, ~0x30, ~1)|RD(~5),		"1,i,w", 0, v9 },

{ "rd",	F3(2, 0x28, 0),			F3(~2, ~0x28, ~0)|SIMM13(~0),		"M,d", 0, v8 }, /* rd %asr1,r */
{ "rd",	F3(2, 0x28, 0),			F3(~2, ~0x28, ~0)|RS1_G0|SIMM13(~0),	"y,d", 0, v6 }, /* rd %y,r */
{ "rd",	F3(2, 0x28, 0)|RS1(1),		F3(~2, ~0x28, ~0)|RS1(~1)|SIMM13(~0),	"E,d", 0, v9 }, /* rd %modes,r */
{ "rd",	F3(2, 0x28, 0)|RS1(2),		F3(~2, ~0x28, ~0)|RS1(~2)|SIMM13(~0),	"P,d", 0, v9 }, /* rd %pc,r */
{ "rd",	F3(2, 0x28, 0)|RS1(3),		F3(~2, ~0x28, ~0)|RS1(~3)|SIMM13(~0),	"W,d", 0, v9 }, /* rd %tick,r */
{ "rd",	F3(2, 0x28, 0)|RS1(4),		F3(~2, ~0x28, ~0)|RS1(~4)|SIMM13(~0),	"p,d", 0, v9 }, /* rd %psr,r */
{ "rd",	F3(2, 0x28, 0)|RS1(5),		F3(~2, ~0x28, ~0)|RS1(~5)|SIMM13(~0),	"w,d", 0, v9 }, /* rd %wim,r */
{ "rd",	F3(2, 0x2b, 0),			F3(~2, ~0x2b, ~0)|RS1_G0|SIMM13(~0),	"t,d", 0, v6 }, /* rd %tbr,r */

 /* FIXME-now: the v9 (ie, delta 2.02) definitions of these conflict with the older ones.  These are the older ones. */
{ "rd",	F3(2, 0x29, 0),			F3(~2, ~0x29, ~0)|RS1_G0|SIMM13(~0),	"p,d", 0, v6 }, /* rd %psr,r */
{ "rd",	F3(2, 0x2a, 0),			F3(~2, ~0x2a, ~0)|RS1_G0|SIMM13(~0),	"w,d", 0, v6 }, /* rd %wim,r */

{ "mov",	F3(2, 0x30, 0),		F3(~2, ~0x30, ~0)|ASI(~0),		"1,2,m", F_ALIAS, v8 }, /* wr r,r,%asrX */
{ "mov",	F3(2, 0x30, 0),		F3(~2, ~0x30, ~0)|RD_G0|ASI(~0),	"1,2,y", F_ALIAS, v6 }, /* wr r,r,%y */
{ "mov",	F3(2, 0x30, 0)|RD(0xe),	F3(~2, ~0x30, ~0)|RD(~0xe)|ASI(~0),	"1,2,Y", F_ALIAS, v9 }, /* wr r,r,%amr */
{ "mov",	F3(2, 0x30, 1),		F3(~2, ~0x30, ~1),			"1,i,m", F_ALIAS, v8 }, /* wr r,i,%asrX */
{ "mov",	F3(2, 0x30, 1),		F3(~2, ~0x30, ~1)|RD_G0,		"1,i,y", F_ALIAS, v6 }, /* wr r,i,%y */
{ "mov",	F3(2, 0x30, 1)|RD(0xe),	F3(~2, ~0x30, ~1)|RD(~0xe),		"1,i,Y", F_ALIAS, v9 }, /* wr r,i,%amr */
{ "mov",	F3(2, 0x31, 0),		F3(~2, ~0x31, ~0)|RD_G0|ASI(~0),	"1,2,p", F_ALIAS, v6 }, /* wr r,r,%psr */
{ "mov",	F3(2, 0x31, 1),		F3(~2, ~0x31, ~1)|RD_G0,		"1,i,p", F_ALIAS, v6 }, /* wr r,i,%psr */
{ "mov",	F3(2, 0x32, 0),		F3(~2, ~0x32, ~0)|RD_G0|ASI(~0),	"1,2,w", F_ALIAS, v6 }, /* wr r,r,%wim */
{ "mov",	F3(2, 0x32, 1),		F3(~2, ~0x32, ~1)|RD_G0,		"1,i,w", F_ALIAS, v6 }, /* wr r,i,%wim */
{ "mov",	F3(2, 0x33, 0),		F3(~2, ~0x33, ~0)|RD_G0|ASI(~0),	"1,2,t", F_ALIAS, v6 }, /* wr r,r,%tbr */
{ "mov",	F3(2, 0x33, 1),		F3(~2, ~0x33, ~1)|RD_G0,		"1,i,t", F_ALIAS, v6 }, /* wr r,i,%tbr */

{ "mov",	F3(2, 0x28, 0),		 F3(~2, ~0x28, ~0)|SIMM13(~0),			"M,d", F_ALIAS, v8 }, /* rd %asr1,r */
{ "mov",	F3(2, 0x28, 0),		 F3(~2, ~0x28, ~0)|RS1_G0|SIMM13(~0),		"y,d", F_ALIAS, v6 }, /* rd %y,r */
{ "mov",	F3(2, 0x28, 0)|RS1(0xe), F3(~2, ~0x28, ~0)|RS1(~0xe)|SIMM13(~0),	"Y,d", F_ALIAS, v9 }, /* rd %amr,r */
{ "mov",	F3(2, 0x29, 0),		 F3(~2, ~0x29, ~0)|RS1_G0|SIMM13(~0),		"p,d", F_ALIAS, v6 }, /* rd %psr,r */
{ "mov",	F3(2, 0x2a, 0),		 F3(~2, ~0x2a, ~0)|RS1_G0|SIMM13(~0),		"w,d", F_ALIAS, v6 }, /* rd %wim,r */
{ "mov",	F3(2, 0x2b, 0),		 F3(~2, ~0x2b, ~0)|RS1_G0|SIMM13(~0),		"t,d", F_ALIAS, v6 }, /* rd %tbr,r */

{ "mov",	F3(2, 0x30, 0), F3(~2, ~0x30, ~0)|ASI_RS2(~0),	"1,y", F_ALIAS, v6 }, /* wr rs1,%g0,%y */
{ "mov",	F3(2, 0x30, 1), F3(~2, ~0x30, ~1),		"i,y", F_ALIAS, v6 },
{ "mov",	F3(2, 0x30, 1), F3(~2, ~0x30, ~1)|SIMM13(~0),	"1,y", F_ALIAS, v6 }, /* wr rs1,0,%y */
{ "mov",	F3(2, 0x31, 0), F3(~2, ~0x31, ~0)|ASI_RS2(~0),	"1,p", F_ALIAS, v6 }, /* wr rs1,%g0,%psr */
{ "mov",	F3(2, 0x31, 1), F3(~2, ~0x31, ~1),		"i,p", F_ALIAS, v6 },
{ "mov",	F3(2, 0x31, 1), F3(~2, ~0x31, ~1)|SIMM13(~0),	"1,p", F_ALIAS, v6 }, /* wr rs1,0,%psr */
{ "mov",	F3(2, 0x32, 0), F3(~2, ~0x32, ~0)|ASI_RS2(~0),	"1,w", F_ALIAS, v6 }, /* wr rs1,%g0,%wim */
{ "mov",	F3(2, 0x32, 1), F3(~2, ~0x32, ~1),		"i,w", F_ALIAS, v6 },
{ "mov",	F3(2, 0x32, 1), F3(~2, ~0x32, ~1)|SIMM13(~0),	"1,w", F_ALIAS, v6 }, /* wr rs1,0,%wim */
{ "mov",	F3(2, 0x33, 0), F3(~2, ~0x33, ~0)|ASI_RS2(~0),	"1,t", F_ALIAS, v6 }, /* wr rs1,%g0,%tbr */
{ "mov",	F3(2, 0x33, 1), F3(~2, ~0x33, ~1),		"i,t", F_ALIAS, v6 },
{ "mov",	F3(2, 0x33, 1), F3(~2, ~0x33, ~1)|SIMM13(~0),	"1,t", F_ALIAS, v6 }, /* wr rs1,0,%tbr */

{ "mov",	F3(2, 0x02, 0), F3(~2, ~0x02, ~0)|RS1_G0|ASI(~0),	"2,d", 0, v6 }, /* or %g0,rs2,d */
{ "mov",	F3(2, 0x02, 1), F3(~2, ~0x02, ~1)|RS1_G0,		"i,d", 0, v6 }, /* or %g0,i,d	*/
{ "mov",        F3(2, 0x02, 0), F3(~2, ~0x02, ~0)|ASI_RS2(~0),		"1,d", 0, v6 }, /* or rs1,%g0,d   */
{ "mov",        F3(2, 0x02, 1), F3(~2, ~0x02, ~1)|SIMM13(~0),		"1,d", 0, v6 }, /* or rs1,0,d */

{ "or",	F3(2, 0x02, 0), F3(~2, ~0x02, ~0)|ASI(~0),	"1,2,d", 0, v6 },
{ "or",	F3(2, 0x02, 1), F3(~2, ~0x02, ~1),		"1,i,d", 0, v6 },
{ "or",	F3(2, 0x02, 1), F3(~2, ~0x02, ~1),		"i,1,d", 0, v6 },

{ "bset",	F3(2, 0x02, 0), F3(~2, ~0x02, ~0)|ASI(~0),	"2,r", F_ALIAS, v6 },	/* or rd,rs2,rd */
{ "bset",	F3(2, 0x02, 1), F3(~2, ~0x02, ~1),		"i,r", F_ALIAS, v6 },	/* or rd,i,rd */

{ "andn",	F3(2, 0x05, 0), F3(~2, ~0x05, ~0)|ASI(~0),	"1,2,d", 0, v6 },
{ "andn",	F3(2, 0x05, 1), F3(~2, ~0x05, ~1),		"1,i,d", 0, v6 },
{ "andn",	F3(2, 0x05, 1), F3(~2, ~0x05, ~1),		"i,1,d", 0, v6 },

{ "andncc",	F3(2, 0x15, 0), F3(~2, ~0x15, ~0)|ASI(~0),	"1,2,d", 0, v6 },
{ "andncc",	F3(2, 0x15, 1), F3(~2, ~0x15, ~1),		"1,i,d", 0, v6 },
{ "andncc",	F3(2, 0x15, 1), F3(~2, ~0x15, ~1),		"i,1,d", 0, v6 },

{ "bclr",	F3(2, 0x05, 0), F3(~2, ~0x05, ~0)|ASI(~0),	"2,r", F_ALIAS, v6 },	/* andn rd,rs2,rd */
{ "bclr",	F3(2, 0x05, 1), F3(~2, ~0x05, ~1),		"i,r", F_ALIAS, v6 },	/* andn rd,i,rd */

{ "cmp",	F3(2, 0x14, 0), F3(~2, ~0x14, ~0)|RD_G0|ASI(~0),	"1,2", 0, v6 },	/* subcc rs1,rs2,%g0 */
{ "cmp",	F3(2, 0x14, 1), F3(~2, ~0x14, ~1)|RD_G0,		"1,i", 0, v6 },	/* subcc rs1,i,%g0 */

{ "sub",	F3(2, 0x04, 0), F3(~2, ~0x04, ~0)|ASI(~0),	"1,2,d", 0, v6 },
{ "sub",	F3(2, 0x04, 1), F3(~2, ~0x04, ~1),		"1,i,d", 0, v6 },

{ "subcc",	F3(2, 0x14, 0), F3(~2, ~0x14, ~0)|ASI(~0),	"1,2,d", 0, v6 },
{ "subcc",	F3(2, 0x14, 1), F3(~2, ~0x14, ~1),		"1,i,d", 0, v6 },

{ "subx",	F3(2, 0x0c, 0), F3(~2, ~0x0c, ~0)|ASI(~0),	"1,2,d", 0, v6 },
{ "subx",	F3(2, 0x0c, 1), F3(~2, ~0x0c, ~1),		"1,i,d", 0, v6 },

{ "subxcc",	F3(2, 0x1c, 0), F3(~2, ~0x1c, ~0)|ASI(~0),	"1,2,d", 0, v6 },
{ "subxcc",	F3(2, 0x1c, 1), F3(~2, ~0x1c, ~1),		"1,i,d", 0, v6 },

{ "and",	F3(2, 0x01, 0), F3(~2, ~0x01, ~0)|ASI(~0),	"1,2,d", 0, v6 },
{ "and",	F3(2, 0x01, 1), F3(~2, ~0x01, ~1),		"1,i,d", 0, v6 },
{ "and",	F3(2, 0x01, 1), F3(~2, ~0x01, ~1),		"i,1,d", 0, v6 },

{ "andcc",	F3(2, 0x11, 0), F3(~2, ~0x11, ~0)|ASI(~0),	"1,2,d", 0, v6 },
{ "andcc",	F3(2, 0x11, 1), F3(~2, ~0x11, ~1),		"1,i,d", 0, v6 },
{ "andcc",	F3(2, 0x11, 1), F3(~2, ~0x11, ~1),		"i,1,d", 0, v6 },

{ "dec",	F3(2, 0x04, 1)|SIMM13(0x1), F3(~2, ~0x04, ~1)|SIMM13(~0x0001), "r", F_ALIAS, v6 },	/* sub rd,1,rd */
{ "deccc",	F3(2, 0x14, 1)|SIMM13(0x1), F3(~2, ~0x14, ~1)|SIMM13(~0x0001), "r", F_ALIAS, v6 },	/* subcc rd,1,rd */
{ "inc",	F3(2, 0x00, 1)|SIMM13(0x1), F3(~2, ~0x00, ~1)|SIMM13(~0x0001), "r", F_ALIAS, v6 },	/* add rs1,1,rsd */
{ "inccc",	F3(2, 0x10, 1)|SIMM13(0x1), F3(~2, ~0x10, ~1)|SIMM13(~0x0001), "r", F_ALIAS, v6 },	/* addcc rd,1,rd */

{ "btst",	F3(2, 0x11, 0), F3(~2, ~0x11, ~0)|RD_G0|ASI(~0), "1,2", F_ALIAS, v6 },	/* andcc rs1,rs2,%g0 */
{ "btst",	F3(2, 0x11, 1), F3(~2, ~0x11, ~1)|RD_G0, "i,1", F_ALIAS, v6 },	/* andcc rs1,i,%g0 */

{ "neg",	F3(2, 0x04, 0), F3(~2, ~0x04, ~0)|RS1_G0|ASI(~0), "2,d", F_ALIAS, v6 }, /* sub %g0,rs2,rd */
{ "neg",	F3(2, 0x04, 0), F3(~2, ~0x04, ~0)|RS1_G0|ASI(~0), "r", F_ALIAS, v6 }, /* sub %g0,rd,rd */

{ "add",	F3(2, 0x00, 0), F3(~2, ~0x00, ~0)|ASI(~0),	"1,2,d", 0, v6 },
{ "add",	F3(2, 0x00, 1), F3(~2, ~0x00, ~1),		"1,i,d", 0, v6 },
{ "add",	F3(2, 0x00, 1), F3(~2, ~0x00, ~1),		"i,1,d", 0, v6 },
{ "addcc",	F3(2, 0x10, 0), F3(~2, ~0x10, ~0)|ASI(~0),	"1,2,d", 0, v6 },
{ "addcc",	F3(2, 0x10, 1), F3(~2, ~0x10, ~1),		"1,i,d", 0, v6 },
{ "addcc",	F3(2, 0x10, 1), F3(~2, ~0x10, ~1),		"i,1,d", 0, v6 },
{ "addx",	F3(2, 0x08, 0), F3(~2, ~0x08, ~0)|ASI(~0),	"1,2,d", 0, v6 },
{ "addx",	F3(2, 0x08, 1), F3(~2, ~0x08, ~1),		"1,i,d", 0, v6 },
{ "addx",	F3(2, 0x08, 1), F3(~2, ~0x08, ~1),		"i,1,d", 0, v6 },
{ "addxcc",	F3(2, 0x18, 0), F3(~2, ~0x18, ~0)|ASI(~0),	"1,2,d", 0, v6 },
{ "addxcc",	F3(2, 0x18, 1), F3(~2, ~0x18, ~1),		"1,i,d", 0, v6 },
{ "addxcc",	F3(2, 0x18, 1), F3(~2, ~0x18, ~1),		"i,1,d", 0, v6 },

{ "smul",	F3(2, 0x0b, 0), F3(~2, ~0x0b, ~0)|ASI(~0),	"1,2,d", 0, v8 },
{ "smul",	F3(2, 0x0b, 1), F3(~2, ~0x0b, ~1),		"1,i,d", 0, v8 },
{ "smul",	F3(2, 0x0b, 1), F3(~2, ~0x0b, ~1),		"i,1,d", 0, v8 },
{ "smulcc",	F3(2, 0x1b, 0), F3(~2, ~0x1b, ~0)|ASI(~0),	"1,2,d", 0, v8 },
{ "smulcc",	F3(2, 0x1b, 1), F3(~2, ~0x1b, ~1),		"1,i,d", 0, v8 },
{ "smulcc",	F3(2, 0x1b, 1), F3(~2, ~0x1b, ~1),		"i,1,d", 0, v8 },
{ "umul",	F3(2, 0x0a, 0), F3(~2, ~0x0a, ~0)|ASI(~0),	"1,2,d", 0, v8 },
{ "umul",	F3(2, 0x0a, 1), F3(~2, ~0x0a, ~1),		"1,i,d", 0, v8 },
{ "umul",	F3(2, 0x0a, 1), F3(~2, ~0x0a, ~1),		"i,1,d", 0, v8 },
{ "umulcc",	F3(2, 0x1a, 0), F3(~2, ~0x1a, ~0)|ASI(~0),	"1,2,d", 0, v8 },
{ "umulcc",	F3(2, 0x1a, 1), F3(~2, ~0x1a, ~1),		"1,i,d", 0, v8 },
{ "umulcc",	F3(2, 0x1a, 1), F3(~2, ~0x1a, ~1),		"i,1,d", 0, v8 },
{ "sdiv",	F3(2, 0x0f, 0), F3(~2, ~0x0f, ~0)|ASI(~0),	"1,2,d", 0, v8 },
{ "sdiv",	F3(2, 0x0f, 1), F3(~2, ~0x0f, ~1),		"1,i,d", 0, v8 },
{ "sdiv",	F3(2, 0x0f, 1), F3(~2, ~0x0f, ~1),		"i,1,d", 0, v8 },
{ "sdivcc",	F3(2, 0x1f, 0), F3(~2, ~0x1f, ~0)|ASI(~0),	"1,2,d", 0, v8 },
{ "sdivcc",	F3(2, 0x1f, 1), F3(~2, ~0x1f, ~1),		"1,i,d", 0, v8 },
{ "sdivcc",	F3(2, 0x1f, 1), F3(~2, ~0x1f, ~1),		"i,1,d", 0, v8 },
{ "udiv",	F3(2, 0x0e, 0), F3(~2, ~0x0e, ~0)|ASI(~0),	"1,2,d", 0, v8 },
{ "udiv",	F3(2, 0x0e, 1), F3(~2, ~0x0e, ~1),		"1,i,d", 0, v8 },
{ "udiv",	F3(2, 0x0e, 1), F3(~2, ~0x0e, ~1),		"i,1,d", 0, v8 },
{ "udivcc",	F3(2, 0x1e, 0), F3(~2, ~0x1e, ~0)|ASI(~0),	"1,2,d", 0, v8 },
{ "udivcc",	F3(2, 0x1e, 1), F3(~2, ~0x1e, ~1),		"1,i,d", 0, v8 },
{ "udivcc",	F3(2, 0x1e, 1), F3(~2, ~0x1e, ~1),		"i,1,d", 0, v8 },

{ "mulx",	F3(2, 0x09, 0), F3(~2, ~0x09, ~0)|ASI(~0),	"1,2,d", 0, v9 },
{ "mulx",	F3(2, 0x09, 1), F3(~2, ~0x09, ~1),		"1,i,d", 0, v9 },
{ "umulxcc",	F3(2, 0x19, 0), F3(~2, ~0x19, ~0)|ASI(~0),	"1,2,d", 0, v9 },
{ "umulxcc",	F3(2, 0x19, 1), F3(~2, ~0x19, ~1),		"1,i,d", 0, v9 },
{ "sdivx",	F3(2, 0x1d, 0), F3(~2, ~0x1d, ~0)|ASI(~0),	"1,2,d", 0, v9 },
{ "sdivx",	F3(2, 0x1d, 1), F3(~2, ~0x1d, ~1),		"1,i,d", 0, v9 },
{ "udivx",	F3(2, 0x0d, 0), F3(~2, ~0x0d, ~0)|ASI(~0),	"1,2,d", 0, v9 },
{ "udivx",	F3(2, 0x0d, 1), F3(~2, ~0x0d, ~1),		"1,i,d", 0, v9 },

{ "call",	F1(0x1), F1(~0x1), "L", F_DELAYED, v6 },
{ "call",	F1(0x1), F1(~0x1), "L,#", F_DELAYED, v6 },
{ "call",	F3(2, 0x38, 0)|RD(0xf), F3(~2, ~0x38, ~0)|RD(~0xf)|ASI_RS2(~0), "1", F_DELAYED, v6 }, /* jmpl rs1+%g0, %o7 */
{ "call",	F3(2, 0x38, 0)|RD(0xf), F3(~2, ~0x38, ~0)|RD(~0xf)|ASI_RS2(~0), "1,#", F_DELAYED, v6 },

/* Conditional instructions.

   Because this part of the table was such a mess earlier, I have
   macrofied it so that all the branches and traps are generated from
   a single-line description of each condition value.  John Gilmore. */

/* Define branches -- one annulled, one without, etc. */
#define br(opcode, mask, lose, flags) \
 { opcode, (mask)|ANNUL, (lose),       ",al",   (flags), v6 }, \
 { opcode, (mask)      , (lose)|ANNUL, "l",     (flags), v6 }

#define brx(opcode, mask, lose, flags) /* v9 */ \
 { opcode, (mask), (lose)|ANNUL|BPRED, "Z,G",   (flags), v9 }, \
 { opcode, (mask), (lose)|ANNUL|BPRED, ",NZ,G",   (flags), v9 }, \
 { opcode, (mask)|ANNUL, (lose)|BPRED, ",aZ,G", (flags), v9 }, \
 { opcode, (mask)|ANNUL, (lose)|BPRED, ",a,NZ,G", (flags), v9 }, \
 { opcode, (mask)|BPRED, (lose)|ANNUL, ",TZ,G",   (flags), v9 }, \
 { opcode, (mask)|ANNUL|BPRED, (lose), ",a,TZ,G", (flags), v9 }, \
 { opcode, (mask), (lose)|ANNUL|BPRED, "z,G",   (flags), v9 }, \
 { opcode, (mask), (lose)|ANNUL|BPRED, ",Nz,G",   (flags), v9 }, \
 { opcode, (mask)|ANNUL, (lose)|BPRED, ",az,G", (flags), v9 }, \
 { opcode, (mask)|ANNUL, (lose)|BPRED, ",a,Nz,G", (flags), v9 }, \
 { opcode, (mask)|BPRED, (lose)|ANNUL, ",Tz,G",   (flags), v9 }, \
 { opcode, (mask)|ANNUL|BPRED, (lose), ",a,Tz,G", (flags), v9 }

/* Define four traps: reg+reg, reg + immediate, immediate alone, reg alone. */
#define tr(opcode, mask, lose, flags) \
 { opcode, (mask)|IMMED, (lose)|RS1_G0,		"i",     (flags), v6 }, /* %g0 + imm */ \
 { opcode, (mask)|IMMED, (lose),		"1+i",   (flags), v6 }, /* rs1 + imm */ \
 { opcode, (mask), IMMED|(lose),		"1+2",   (flags), v6 }, /* rs1 + rs2 */ \
 { opcode, (mask)|(1<<12)|IMMED, (lose)|RS1_G0,	"Z,i",   (flags), v9 }, /* %g0 + imm */ \
 { opcode, (mask)|(1<<12)|IMMED, (lose),	"Z,1+i", (flags), v9 }, /* rs1 + imm */ \
 { opcode, (mask)|(1<<12), IMMED|(lose),	"Z,1+2", (flags), v9 }, /* rs1 + rs2 */ \
 { opcode, (mask)|(1<<12), IMMED|(lose)|RS2_G0,	"Z,1",   (flags), v9 }, /* rs1 + %g0 */ \
 { opcode, (mask)|IMMED, (1<<12)|(lose)|RS1_G0,	"z,i",   (flags)|F_ALIAS, v9 }, /* %g0 + imm */ \
 { opcode, (mask)|IMMED, (1<<12)|(lose),	"z,1+i", (flags)|F_ALIAS, v9 }, /* rs1 + imm */ \
 { opcode, (mask), IMMED|(1<<12)|(lose),	"z,1+2", (flags)|F_ALIAS, v9 }, /* rs1 + rs2 */ \
 { opcode, (mask), IMMED|(1<<12)|(lose)|RS2_G0,	"z,1",   (flags)|F_ALIAS, v9 }, /* rs1 + %g0 */ \
 { opcode, (mask), IMMED|(lose)|RS2_G0,		"1",     (flags), v6 } /* rs1 + %g0 */

/* Define both branches and traps based on condition mask */
#define cond(bop, top, mask, flags) \
  br(bop,  F2(0, 2)|(mask), F2(~0, ~2)|((~mask)&COND(~0)), F_DELAYED|(flags)), \
  brx(bop, F2(0, 1)|(mask), F2(~0, ~1)|((~mask)&COND(~0)), F_DELAYED|(flags)), /* v9 */ \
  tr(top,  F3(2, 0x3a, 0)|(mask), F3(~2, ~0x3a, 0)|((~mask)&COND(~0)), (flags))

/* Define all the conditions, all the branches, all the traps.  */

cond ("b",	"t",    CONDA, 0),
cond ("ba",	"ta",   CONDA, F_ALIAS), /* for nothing */
cond ("bcc",	"tcc",  CONDCC, 0),
cond ("bcs",	"tcs",  CONDCS, 0),
cond ("be",	"te",   CONDE, 0),
cond ("bg",	"tg",   CONDG, 0),
cond ("bgt",	"tgt",   CONDG, F_ALIAS),
cond ("bge",	"tge",  CONDGE, 0),
cond ("bgeu",	"tgeu", CONDGEU, F_ALIAS), /* for cc */
cond ("bgu",	"tgu",  CONDGU, 0),
cond ("bl",	"tl",   CONDL, 0),
cond ("blt",	"tlt",   CONDL, F_ALIAS),
cond ("ble",	"tle",  CONDLE, 0),
cond ("bleu",	"tleu", CONDLEU, 0),
cond ("blu",	"tlu",  CONDLU, F_ALIAS), /* for cs */
cond ("bn",	"tn",   CONDN, 0),
cond ("bne",	"tne",  CONDNE, 0),
cond ("bneg",	"tneg", CONDNEG, 0),
cond ("bnz",	"tnz",  CONDNZ, F_ALIAS), /* for ne */
cond ("bpos",	"tpos", CONDPOS, 0),
cond ("bvc",	"tvc",  CONDVC, 0),
cond ("bvs",	"tvs",  CONDVS, 0),
cond ("bz",	"tz",   CONDZ, F_ALIAS), /* for e */

#undef cond
#undef br
#undef tr

#define brr(opcode, mask, lose, flags) /* v9 */ \
 { opcode, (mask), (lose)|ANNUL|BPRED, "k",   F_DELAYED|(flags), v9 }, \
 { opcode, (mask), (lose)|ANNUL|BPRED, ",Nk", F_DELAYED|(flags), v9 }, \
 { opcode, (mask)|ANNUL, (lose)|BPRED, ",ak", F_DELAYED|(flags), v9 }, \
 { opcode, (mask)|ANNUL, (lose)|BPRED, ",a,Nk", F_DELAYED|(flags), v9 }, \
 { opcode, (mask)|BPRED, (lose)|ANNUL, ",Tk",   F_DELAYED|(flags), v9 }, \
 { opcode, (mask)|ANNUL|BPRED, (lose), ",a,Tk", F_DELAYED|(flags), v9 }

#define condr(bop, mask, flags) /* v9 */ \
  brr(bop, F2(0, 3)|COND(mask), F2(~0, ~3)|COND(~(mask)), (flags)) /* v9 */ \

/* v9 */ condr("bre", 0x1, 0),
/* v9 */ condr("brne", 0x0, 0),
/* v9 */ condr("brneg", 0x3, 0),
/* v9 */ condr("brnz", 0x0, F_ALIAS),
/* v9 */ condr("brpos", 0x2, 0),
/* v9 */ condr("brz", 0x1, F_ALIAS),

#undef condr /* v9 */
#undef brr /* v9 */

#define mrr(opcode, mask, lose, flags) /* v9 */ \
 { opcode, (mask), (lose)|ASI(~0), "1,2,d",   F_DELAYED|(flags), v9 }, \
 { opcode, (mask), (lose), "1,i,d", F_DELAYED|(flags), v9 }

#define movr(bop, mask, flags) /* v9 */ \
  mrr(bop, F3(2, 0x2f, 0)|COND(mask), F3(~2, ~0x2f, ~0)|COND(~(mask))|ASI(~0), (flags)), /* v9 */ \
  mrr(bop, F3(2, 0x2f, 1)|COND(mask), F3(~2, ~0x2f, ~1)|COND(~(mask)), (flags)) /* v9 */ \

/* v9 */ movr("movre", 0x1, 0),
/* v9 */ movr("movrne", 0x0, 0),
/* v9 */ movr("movrneg", 0x3, 0),
/* v9 */ movr("movrnz", 0x0, F_ALIAS),
/* v9 */ movr("movrpos", 0x2, 0),
/* v9 */ movr("movrz", 0x1, F_ALIAS),

#undef movr /* v9 */
#undef mrr /* v9 */

{ "mova",	F2(2, 0x58)|FCC(0)|MCOND(FCONDA), MCOND(~FCONDA)|IMMED|FCC(~0)|F2(~2, ~0x58), "6,2,d", 0, v9 },
{ "mova",	F2(2, 0x58)|FCC(0)|MCOND(FCONDA)|IMMED, MCOND(~FCONDA)|FCC(~0)|F2(~2, ~0x58), "6,I,d", 0, v9 },
{ "mova",	F2(2, 0x58)|FCC(1)|MCOND(FCONDA), IMMED|MCOND(~FCONDA)|FCC(~1)|F2(~2, ~0x58), "7,2,d", 0, v9 },
{ "mova",	F2(2, 0x58)|FCC(1)|MCOND(FCONDA)|IMMED, MCOND(~FCONDA)|FCC(~1)|F2(~2, ~0x58), "7,I,d", 0, v9 },
{ "mova",	F2(2, 0x58)|FCC(2)|MCOND(FCONDA), IMMED|MCOND(~FCONDA)|FCC(~2)|F2(~2, ~0x58), "8,2,d", 0, v9 },
{ "mova",	F2(2, 0x58)|FCC(2)|MCOND(FCONDA)|IMMED, MCOND(~FCONDA)|FCC(~2)|F2(~2, ~0x58), "8,I,d", 0, v9 },
{ "mova",	F2(2, 0x58)|FCC(3)|MCOND(FCONDA), IMMED|MCOND(~FCONDA)|FCC(~3)|F2(~2, ~0x58), "9,2,d", 0, v9 },
{ "mova",	F2(2, 0x58)|FCC(3)|MCOND(FCONDA)|IMMED, MCOND(~FCONDA)|FCC(~3)|F2(~2, ~0x58), "9,I,d", 0, v9 },
{ "mova",	F2(2, 0x59)|MCOND(CONDA)|ICC, F2(~2, ~0x59)|MCOND(~CONDA)|IMMED|XCC|(1<<12), "z,2,d", 0, v9 },
{ "mova",	F2(2, 0x59)|MCOND(CONDA)|ICC|IMMED, F2(~2, ~0x59)|MCOND(~CONDA)|XCC|(1<<12), "z,I,d", 0, v9 },
{ "mova",	F2(2, 0x59)|MCOND(CONDA)|XCC, F2(~2, ~0x59)|MCOND(~CONDA)|IMMED|(1<<12), "Z,2,d", 0, v9 },
{ "mova",	F2(2, 0x59)|MCOND(CONDA)|XCC|IMMED, F2(~2, ~0x59)|MCOND(~CONDA)|(1<<12), "Z,I,d", 0, v9 },
{ "movcc",	F2(2, 0x59)|MCOND(CONDCC)|ICC, F2(~2, ~0x59)|MCOND(~CONDCC)|IMMED|XCC|(1<<12), "z,2,d", 0, v9 },
{ "movcc",	F2(2, 0x59)|MCOND(CONDCC)|ICC|IMMED, F2(~2, ~0x59)|MCOND(~CONDCC)|XCC|(1<<12), "z,I,d", 0, v9 },
{ "movcc",	F2(2, 0x59)|MCOND(CONDCC)|XCC, F2(~2, ~0x59)|MCOND(~CONDCC)|IMMED|(1<<12), "Z,2,d", 0, v9 },
{ "movcc",	F2(2, 0x59)|MCOND(CONDCC)|XCC|IMMED, F2(~2, ~0x59)|MCOND(~CONDCC)|(1<<12), "Z,I,d", 0, v9 },
{ "movcs",	F2(2, 0x59)|MCOND(CONDCS)|ICC, F2(~2, ~0x59)|MCOND(~CONDCS)|IMMED|XCC|(1<<12), "z,2,d", 0, v9 },
{ "movcs",	F2(2, 0x59)|MCOND(CONDCS)|ICC|IMMED, F2(~2, ~0x59)|MCOND(~CONDCS)|XCC|(1<<12), "z,I,d", 0, v9 },
{ "movcs",	F2(2, 0x59)|MCOND(CONDCS)|XCC, F2(~2, ~0x59)|MCOND(~CONDCS)|IMMED|(1<<12), "Z,2,d", 0, v9 },
{ "movcs",	F2(2, 0x59)|MCOND(CONDCS)|XCC|IMMED, F2(~2, ~0x59)|MCOND(~CONDCS)|(1<<12), "Z,I,d", 0, v9 },
{ "move",	F2(2, 0x58)|FCC(0)|MCOND(FCONDE), IMMED|MCOND(~FCONDE)|FCC(~0)|F2(~2, ~0x58), "6,2,d", 0, v9 },
{ "move",	F2(2, 0x58)|FCC(0)|MCOND(FCONDE)|IMMED, MCOND(~FCONDE)|FCC(~0)|F2(~2, ~0x58), "6,I,d", 0, v9 },
{ "move",	F2(2, 0x58)|FCC(1)|MCOND(FCONDE), IMMED|MCOND(~FCONDE)|FCC(~1)|F2(~2, ~0x58), "7,2,d", 0, v9 },
{ "move",	F2(2, 0x58)|FCC(1)|MCOND(FCONDE)|IMMED, MCOND(~FCONDE)|FCC(~1)|F2(~2, ~0x58), "7,I,d", 0, v9 },
{ "move",	F2(2, 0x58)|FCC(2)|MCOND(FCONDE), IMMED|MCOND(~FCONDE)|FCC(~2)|F2(~2, ~0x58), "8,2,d", 0, v9 },
{ "move",	F2(2, 0x58)|FCC(2)|MCOND(FCONDE)|IMMED, MCOND(~FCONDE)|FCC(~2)|F2(~2, ~0x58), "8,I,d", 0, v9 },
{ "move",	F2(2, 0x58)|FCC(3)|MCOND(FCONDE), IMMED|MCOND(~FCONDE)|FCC(~3)|F2(~2, ~0x58), "9,2,d", 0, v9 },
{ "move",	F2(2, 0x58)|FCC(3)|MCOND(FCONDE)|IMMED, MCOND(~FCONDE)|FCC(~3)|F2(~2, ~0x58), "9,I,d", 0, v9 },
{ "move",	F2(2, 0x59)|MCOND(CONDE)|ICC, F2(~2, ~0x59)|MCOND(~CONDE)|IMMED|XCC|(1<<12), "z,2,d", 0, v9 },
{ "move",	F2(2, 0x59)|MCOND(CONDE)|ICC|IMMED, F2(~2, ~0x59)|MCOND(~CONDE)|XCC|(1<<12), "z,I,d", 0, v9 },
{ "move",	F2(2, 0x59)|MCOND(CONDE)|XCC, F2(~2, ~0x59)|MCOND(~CONDE)|IMMED|(1<<12), "Z,2,d", 0, v9 },
{ "move",	F2(2, 0x59)|MCOND(CONDE)|XCC|IMMED, F2(~2, ~0x59)|MCOND(~CONDE)|(1<<12), "Z,I,d", 0, v9 },
{ "movg",	F2(2, 0x58)|FCC(0)|MCOND(FCONDG), IMMED|MCOND(~FCONDG)|FCC(~0)|F2(~2, ~0x58), "6,2,d", 0, v9 },
{ "movg",	F2(2, 0x58)|FCC(0)|MCOND(FCONDG)|IMMED, MCOND(~FCONDG)|FCC(~0)|F2(~2, ~0x58), "6,I,d", 0, v9 },
{ "movg",	F2(2, 0x58)|FCC(1)|MCOND(FCONDG), IMMED|MCOND(~FCONDG)|FCC(~1)|F2(~2, ~0x58), "7,2,d", 0, v9 },
{ "movg",	F2(2, 0x58)|FCC(1)|MCOND(FCONDG)|IMMED, MCOND(~FCONDG)|FCC(~1)|F2(~2, ~0x58), "7,I,d", 0, v9 },
{ "movg",	F2(2, 0x58)|FCC(2)|MCOND(FCONDG), IMMED|MCOND(~FCONDG)|FCC(~2)|F2(~2, ~0x58), "8,2,d", 0, v9 },
{ "movg",	F2(2, 0x58)|FCC(2)|MCOND(FCONDG)|IMMED, MCOND(~FCONDG)|FCC(~2)|F2(~2, ~0x58), "8,I,d", 0, v9 },
{ "movg",	F2(2, 0x58)|FCC(3)|MCOND(FCONDG), IMMED|MCOND(~FCONDG)|FCC(~3)|F2(~2, ~0x58), "9,2,d", 0, v9 },
{ "movg",	F2(2, 0x58)|FCC(3)|MCOND(FCONDG)|IMMED, MCOND(~FCONDG)|FCC(~3)|F2(~2, ~0x58), "9,I,d", 0, v9 },
{ "movg",	F2(2, 0x59)|MCOND(CONDG)|ICC, F2(~2, ~0x59)|MCOND(~CONDG)|IMMED|XCC|(1<<12), "z,2,d", 0, v9 },
{ "movg",	F2(2, 0x59)|MCOND(CONDG)|ICC|IMMED, F2(~2, ~0x59)|MCOND(~CONDG)|XCC|(1<<12), "z,I,d", 0, v9 },
{ "movg",	F2(2, 0x59)|MCOND(CONDG)|XCC, F2(~2, ~0x59)|MCOND(~CONDG)|IMMED|(1<<12), "Z,2,d", 0, v9 },
{ "movg",	F2(2, 0x59)|MCOND(CONDG)|XCC|IMMED, F2(~2, ~0x59)|MCOND(~CONDG)|(1<<12), "Z,I,d", 0, v9 },
{ "movge",	F2(2, 0x58)|FCC(0)|MCOND(FCONDGE), IMMED|MCOND(~FCONDGE)|FCC(~0)|F2(~2, ~0x58), "6,2,d", 0, v9 },
{ "movge",	F2(2, 0x58)|FCC(0)|MCOND(FCONDGE)|IMMED, MCOND(~FCONDGE)|FCC(~0)|F2(~2, ~0x58), "6,I,d", 0, v9 },
{ "movge",	F2(2, 0x58)|FCC(1)|MCOND(FCONDGE), IMMED|MCOND(~FCONDGE)|FCC(~1)|F2(~2, ~0x58), "7,2,d", 0, v9 },
{ "movge",	F2(2, 0x58)|FCC(1)|MCOND(FCONDGE)|IMMED, MCOND(~FCONDGE)|FCC(~1)|F2(~2, ~0x58), "7,I,d", 0, v9 },
{ "movge",	F2(2, 0x58)|FCC(2)|MCOND(FCONDGE), IMMED|MCOND(~FCONDGE)|FCC(~2)|F2(~2, ~0x58), "8,2,d", 0, v9 },
{ "movge",	F2(2, 0x58)|FCC(2)|MCOND(FCONDGE)|IMMED, MCOND(~FCONDGE)|FCC(~2)|F2(~2, ~0x58), "8,I,d", 0, v9 },
{ "movge",	F2(2, 0x58)|FCC(3)|MCOND(FCONDGE), IMMED|MCOND(~FCONDGE)|FCC(~3)|F2(~2, ~0x58), "9,2,d", 0, v9 },
{ "movge",	F2(2, 0x58)|FCC(3)|MCOND(FCONDGE)|IMMED, MCOND(~FCONDGE)|FCC(~3)|F2(~2, ~0x58), "9,I,d", 0, v9 },
{ "movge",	F2(2, 0x59)|MCOND(CONDGE)|ICC, F2(~2, ~0x59)|MCOND(~CONDGE)|IMMED|XCC|(1<<12), "z,2,d", 0, v9 },
{ "movge",	F2(2, 0x59)|MCOND(CONDGE)|ICC|IMMED, F2(~2, ~0x59)|MCOND(~CONDGE)|XCC|(1<<12), "z,I,d", 0, v9 },
{ "movge",	F2(2, 0x59)|MCOND(CONDGE)|XCC, F2(~2, ~0x59)|MCOND(~CONDGE)|IMMED|(1<<12), "Z,2,d", 0, v9 },
{ "movge",	F2(2, 0x59)|MCOND(CONDGE)|XCC|IMMED, F2(~2, ~0x59)|MCOND(~CONDGE)|(1<<12), "Z,I,d", 0, v9 },
{ "movgu",	F2(2, 0x59)|MCOND(CONDGU)|ICC, F2(~2, ~0x59)|MCOND(~CONDGU)|IMMED|XCC|(1<<12), "z,2,d", 0, v9 },
{ "movgu",	F2(2, 0x59)|MCOND(CONDGU)|ICC|IMMED, F2(~2, ~0x59)|MCOND(~CONDGU)|XCC|(1<<12), "z,I,d", 0, v9 },
{ "movgu",	F2(2, 0x59)|MCOND(CONDGU)|XCC, F2(~2, ~0x59)|MCOND(~CONDGU)|IMMED|(1<<12), "Z,2,d", 0, v9 },
{ "movgu",	F2(2, 0x59)|MCOND(CONDGU)|XCC|IMMED, F2(~2, ~0x59)|MCOND(~CONDGU)|(1<<12), "Z,I,d", 0, v9 },
{ "movl",	F2(2, 0x58)|FCC(0)|MCOND(FCONDL), IMMED|MCOND(~FCONDL)|FCC(~0)|F2(~2, ~0x58), "6,2,d", 0, v9 },
{ "movl",	F2(2, 0x58)|FCC(0)|MCOND(FCONDL)|IMMED, MCOND(~FCONDL)|FCC(~0)|F2(~2, ~0x58), "6,I,d", 0, v9 },
{ "movl",	F2(2, 0x58)|FCC(1)|MCOND(FCONDL), IMMED|MCOND(~FCONDL)|FCC(~1)|F2(~2, ~0x58), "7,2,d", 0, v9 },
{ "movl",	F2(2, 0x58)|FCC(1)|MCOND(FCONDL)|IMMED, MCOND(~FCONDL)|FCC(~1)|F2(~2, ~0x58), "7,I,d", 0, v9 },
{ "movl",	F2(2, 0x58)|FCC(2)|MCOND(FCONDL), IMMED|MCOND(~FCONDL)|FCC(~2)|F2(~2, ~0x58), "8,2,d", 0, v9 },
{ "movl",	F2(2, 0x58)|FCC(2)|MCOND(FCONDL)|IMMED, MCOND(~FCONDL)|FCC(~2)|F2(~2, ~0x58), "8,I,d", 0, v9 },
{ "movl",	F2(2, 0x58)|FCC(3)|MCOND(FCONDL), IMMED|MCOND(~FCONDL)|FCC(~3)|F2(~2, ~0x58), "9,2,d", 0, v9 },
{ "movl",	F2(2, 0x58)|FCC(3)|MCOND(FCONDL)|IMMED, MCOND(~FCONDL)|FCC(~3)|F2(~2, ~0x58), "9,I,d", 0, v9 },
{ "movl",	F2(2, 0x59)|MCOND(CONDL)|ICC, F2(~2, ~0x59)|MCOND(~CONDL)|IMMED|XCC|(1<<12), "z,2,d", 0, v9 },
{ "movl",	F2(2, 0x59)|MCOND(CONDL)|ICC|IMMED, F2(~2, ~0x59)|MCOND(~CONDL)|XCC|(1<<12), "z,I,d", 0, v9 },
{ "movl",	F2(2, 0x59)|MCOND(CONDL)|XCC, F2(~2, ~0x59)|MCOND(~CONDL)|IMMED|(1<<12), "Z,2,d", 0, v9 },
{ "movl",	F2(2, 0x59)|MCOND(CONDL)|XCC|IMMED, F2(~2, ~0x59)|MCOND(~CONDL)|(1<<12), "Z,I,d", 0, v9 },
{ "movle",	F2(2, 0x58)|FCC(0)|MCOND(FCONDLE), IMMED|MCOND(~FCONDLE)|FCC(~0)|F2(~2, ~0x58), "6,2,d", 0, v9 },
{ "movle",	F2(2, 0x58)|FCC(0)|MCOND(FCONDLE)|IMMED, MCOND(~FCONDLE)|FCC(~0)|F2(~2, ~0x58), "6,I,d", 0, v9 },
{ "movle",	F2(2, 0x58)|FCC(1)|MCOND(FCONDLE), IMMED|MCOND(~FCONDLE)|FCC(~1)|F2(~2, ~0x58), "7,2,d", 0, v9 },
{ "movle",	F2(2, 0x58)|FCC(1)|MCOND(FCONDLE)|IMMED, MCOND(~FCONDLE)|FCC(~1)|F2(~2, ~0x58), "7,I,d", 0, v9 },
{ "movle",	F2(2, 0x58)|FCC(2)|MCOND(FCONDLE), IMMED|MCOND(~FCONDLE)|FCC(~2)|F2(~2, ~0x58), "8,2,d", 0, v9 },
{ "movle",	F2(2, 0x58)|FCC(2)|MCOND(FCONDLE)|IMMED, MCOND(~FCONDLE)|FCC(~2)|F2(~2, ~0x58), "8,I,d", 0, v9 },
{ "movle",	F2(2, 0x58)|FCC(3)|MCOND(FCONDLE), IMMED|MCOND(~FCONDLE)|FCC(~3)|F2(~2, ~0x58), "9,2,d", 0, v9 },
{ "movle",	F2(2, 0x58)|FCC(3)|MCOND(FCONDLE)|IMMED, MCOND(~FCONDLE)|FCC(~3)|F2(~2, ~0x58), "9,I,d", 0, v9 },
{ "movle",	F2(2, 0x59)|MCOND(CONDLE)|ICC, F2(~2, ~0x59)|MCOND(~CONDLE)|IMMED|XCC|(1<<12), "z,2,d", 0, v9 },
{ "movle",	F2(2, 0x59)|MCOND(CONDLE)|ICC|IMMED, F2(~2, ~0x59)|MCOND(~CONDLE)|XCC|(1<<12), "z,I,d", 0, v9 },
{ "movle",	F2(2, 0x59)|MCOND(CONDLE)|XCC, F2(~2, ~0x59)|MCOND(~CONDLE)|IMMED|(1<<12), "Z,2,d", 0, v9 },
{ "movle",	F2(2, 0x59)|MCOND(CONDLE)|XCC|IMMED, F2(~2, ~0x59)|MCOND(~CONDLE)|(1<<12), "Z,I,d", 0, v9 },
{ "movleu",	F2(2, 0x59)|MCOND(CONDLEU)|ICC, F2(~2, ~0x59)|MCOND(~CONDLEU)|IMMED|XCC|(1<<12), "z,2,d", 0, v9 },
{ "movleu",	F2(2, 0x59)|MCOND(CONDLEU)|ICC|IMMED, F2(~2, ~0x59)|MCOND(~CONDLEU)|XCC|(1<<12), "z,I,d", 0, v9 },
{ "movleu",	F2(2, 0x59)|MCOND(CONDLEU)|XCC, F2(~2, ~0x59)|MCOND(~CONDLEU)|IMMED|(1<<12), "Z,2,d", 0, v9 },
{ "movleu",	F2(2, 0x59)|MCOND(CONDLEU)|XCC|IMMED, F2(~2, ~0x59)|MCOND(~CONDLEU)|(1<<12), "Z,I,d", 0, v9 },
{ "movlg",	F2(2, 0x58)|FCC(0)|MCOND(FCONDLG), IMMED|MCOND(~FCONDLG)|FCC(~0)|F2(~2, ~0x58), "6,2,d", 0, v9 },
{ "movlg",	F2(2, 0x58)|FCC(0)|MCOND(FCONDLG)|IMMED, MCOND(~FCONDLG)|FCC(~0)|F2(~2, ~0x58), "6,I,d", 0, v9 },
{ "movlg",	F2(2, 0x58)|FCC(1)|MCOND(FCONDLG), IMMED|MCOND(~FCONDLG)|FCC(~1)|F2(~2, ~0x58), "7,2,d", 0, v9 },
{ "movlg",	F2(2, 0x58)|FCC(1)|MCOND(FCONDLG)|IMMED, MCOND(~FCONDLG)|FCC(~1)|F2(~2, ~0x58), "7,I,d", 0, v9 },
{ "movlg",	F2(2, 0x58)|FCC(2)|MCOND(FCONDLG), IMMED|MCOND(~FCONDLG)|FCC(~2)|F2(~2, ~0x58), "8,2,d", 0, v9 },
{ "movlg",	F2(2, 0x58)|FCC(2)|MCOND(FCONDLG)|IMMED, MCOND(~FCONDLG)|FCC(~2)|F2(~2, ~0x58), "8,I,d", 0, v9 },
{ "movlg",	F2(2, 0x58)|FCC(3)|MCOND(FCONDLG), IMMED|MCOND(~FCONDLG)|FCC(~3)|F2(~2, ~0x58), "9,2,d", 0, v9 },
{ "movlg",	F2(2, 0x58)|FCC(3)|MCOND(FCONDLG)|IMMED, MCOND(~FCONDLG)|FCC(~3)|F2(~2, ~0x58), "9,I,d", 0, v9 },
{ "movn",	F2(2, 0x58)|FCC(0)|MCOND(FCONDN), IMMED|MCOND(~FCONDN)|FCC(~0)|F2(~2, ~0x58), "6,2,d", 0, v9 },
{ "movn",	F2(2, 0x58)|FCC(0)|MCOND(FCONDN)|IMMED, MCOND(~FCONDN)|FCC(~0)|F2(~2, ~0x58), "6,I,d", 0, v9 },
{ "movn",	F2(2, 0x58)|FCC(1)|MCOND(FCONDN), IMMED|MCOND(~FCONDN)|FCC(~1)|F2(~2, ~0x58), "7,2,d", 0, v9 },
{ "movn",	F2(2, 0x58)|FCC(1)|MCOND(FCONDN)|IMMED, MCOND(~FCONDN)|FCC(~1)|F2(~2, ~0x58), "7,I,d", 0, v9 },
{ "movn",	F2(2, 0x58)|FCC(2)|MCOND(FCONDN), IMMED|MCOND(~FCONDN)|FCC(~2)|F2(~2, ~0x58), "8,2,d", 0, v9 },
{ "movn",	F2(2, 0x58)|FCC(2)|MCOND(FCONDN)|IMMED, MCOND(~FCONDN)|FCC(~2)|F2(~2, ~0x58), "8,I,d", 0, v9 },
{ "movn",	F2(2, 0x58)|FCC(3)|MCOND(FCONDN), IMMED|MCOND(~FCONDN)|FCC(~3)|F2(~2, ~0x58), "9,2,d", 0, v9 },
{ "movn",	F2(2, 0x58)|FCC(3)|MCOND(FCONDN)|IMMED, MCOND(~FCONDN)|FCC(~3)|F2(~2, ~0x58), "9,I,d", 0, v9 },
{ "movn",	F2(2, 0x59)|MCOND(CONDN)|ICC, F2(~2, ~0x59)|MCOND(~CONDN)|IMMED|XCC|(1<<12), "z,2,d", 0, v9 },
{ "movn",	F2(2, 0x59)|MCOND(CONDN)|ICC|IMMED, F2(~2, ~0x59)|MCOND(~CONDN)|XCC|(1<<12), "z,I,d", 0, v9 },
{ "movn",	F2(2, 0x59)|MCOND(CONDN)|XCC, F2(~2, ~0x59)|MCOND(~CONDN)|IMMED|(1<<12), "Z,2,d", 0, v9 },
{ "movn",	F2(2, 0x59)|MCOND(CONDN)|XCC|IMMED, F2(~2, ~0x59)|MCOND(~CONDN)|(1<<12), "Z,I,d", 0, v9 },
{ "movne",	F2(2, 0x58)|FCC(0)|MCOND(FCONDNE), IMMED|MCOND(~FCONDNE)|FCC(~0)|F2(~2, ~0x58), "6,2,d", 0, v9 },
{ "movne",	F2(2, 0x58)|FCC(0)|MCOND(FCONDNE)|IMMED, MCOND(~FCONDNE)|FCC(~0)|F2(~2, ~0x58), "6,I,d", 0, v9 },
{ "movne",	F2(2, 0x58)|FCC(1)|MCOND(FCONDNE), IMMED|MCOND(~FCONDNE)|FCC(~1)|F2(~2, ~0x58), "7,2,d", 0, v9 },
{ "movne",	F2(2, 0x58)|FCC(1)|MCOND(FCONDNE)|IMMED, MCOND(~FCONDNE)|FCC(~1)|F2(~2, ~0x58), "7,I,d", 0, v9 },
{ "movne",	F2(2, 0x58)|FCC(2)|MCOND(FCONDNE), IMMED|MCOND(~FCONDNE)|FCC(~2)|F2(~2, ~0x58), "8,2,d", 0, v9 },
{ "movne",	F2(2, 0x58)|FCC(2)|MCOND(FCONDNE)|IMMED, MCOND(~FCONDNE)|FCC(~2)|F2(~2, ~0x58), "8,I,d", 0, v9 },
{ "movne",	F2(2, 0x58)|FCC(3)|MCOND(FCONDNE), IMMED|MCOND(~FCONDNE)|FCC(~3)|F2(~2, ~0x58), "9,2,d", 0, v9 },
{ "movne",	F2(2, 0x58)|FCC(3)|MCOND(FCONDNE)|IMMED, MCOND(~FCONDNE)|FCC(~3)|F2(~2, ~0x58), "9,I,d", 0, v9 },
{ "movne",	F2(2, 0x59)|MCOND(CONDNE)|ICC, F2(~2, ~0x59)|MCOND(~CONDNE)|IMMED|XCC|(1<<12), "z,2,d", 0, v9 },
{ "movne",	F2(2, 0x59)|MCOND(CONDNE)|ICC|IMMED, F2(~2, ~0x59)|MCOND(~CONDNE)|XCC|(1<<12), "z,I,d", 0, v9 },
{ "movne",	F2(2, 0x59)|MCOND(CONDNE)|XCC, F2(~2, ~0x59)|MCOND(~CONDNE)|IMMED|(1<<12), "Z,2,d", 0, v9 },
{ "movne",	F2(2, 0x59)|MCOND(CONDNE)|XCC|IMMED, F2(~2, ~0x59)|MCOND(~CONDNE)|(1<<12), "Z,I,d", 0, v9 },
{ "movneg",	F2(2, 0x59)|MCOND(CONDNEG)|ICC, F2(~2, ~0x59)|MCOND(~CONDNEG)|IMMED|XCC|(1<<12), "z,2,d", 0, v9 },
{ "movneg",	F2(2, 0x59)|MCOND(CONDNEG)|ICC|IMMED, F2(~2, ~0x59)|MCOND(~CONDNEG)|XCC|(1<<12), "z,I,d", 0, v9 },
{ "movneg",	F2(2, 0x59)|MCOND(CONDNEG)|XCC, F2(~2, ~0x59)|MCOND(~CONDNEG)|IMMED|(1<<12), "Z,2,d", 0, v9 },
{ "movneg",	F2(2, 0x59)|MCOND(CONDNEG)|XCC|IMMED, F2(~2, ~0x59)|MCOND(~CONDNEG)|(1<<12), "Z,I,d", 0, v9 },
{ "movnz",	F2(2, 0x58)|FCC(0)|MCOND(FCONDNZ), IMMED|MCOND(~FCONDNZ)|FCC(~0)|F2(~2, ~0x58), "6,2,d", 0, v9 },
{ "movnz",	F2(2, 0x58)|FCC(0)|MCOND(FCONDNZ)|IMMED, MCOND(~FCONDNZ)|FCC(~0)|F2(~2, ~0x58), "6,I,d", 0, v9 },
{ "movnz",	F2(2, 0x58)|FCC(1)|MCOND(FCONDNZ), IMMED|MCOND(~FCONDNZ)|FCC(~1)|F2(~2, ~0x58), "7,2,d", 0, v9 },
{ "movnz",	F2(2, 0x58)|FCC(1)|MCOND(FCONDNZ)|IMMED, MCOND(~FCONDNZ)|FCC(~1)|F2(~2, ~0x58), "7,I,d", 0, v9 },
{ "movnz",	F2(2, 0x58)|FCC(2)|MCOND(FCONDNZ), IMMED|MCOND(~FCONDNZ)|FCC(~2)|F2(~2, ~0x58), "8,2,d", 0, v9 },
{ "movnz",	F2(2, 0x58)|FCC(2)|MCOND(FCONDNZ)|IMMED, MCOND(~FCONDNZ)|FCC(~2)|F2(~2, ~0x58), "8,I,d", 0, v9 },
{ "movnz",	F2(2, 0x58)|FCC(3)|MCOND(FCONDNZ), IMMED|MCOND(~FCONDNZ)|FCC(~3)|F2(~2, ~0x58), "9,2,d", 0, v9 },
{ "movnz",	F2(2, 0x58)|FCC(3)|MCOND(FCONDNZ)|IMMED, MCOND(~FCONDNZ)|FCC(~3)|F2(~2, ~0x58), "9,I,d", 0, v9 },
{ "movo",	F2(2, 0x58)|FCC(0)|MCOND(FCONDO), IMMED|MCOND(~FCONDO)|FCC(~0)|F2(~2, ~0x58), "6,2,d", 0, v9 },
{ "movo",	F2(2, 0x58)|FCC(0)|MCOND(FCONDO)|IMMED, MCOND(~FCONDO)|FCC(~0)|F2(~2, ~0x58), "6,I,d", 0, v9 },
{ "movo",	F2(2, 0x58)|FCC(1)|MCOND(FCONDO), IMMED|MCOND(~FCONDO)|FCC(~1)|F2(~2, ~0x58), "7,2,d", 0, v9 },
{ "movo",	F2(2, 0x58)|FCC(1)|MCOND(FCONDO)|IMMED, MCOND(~FCONDO)|FCC(~1)|F2(~2, ~0x58), "7,I,d", 0, v9 },
{ "movo",	F2(2, 0x58)|FCC(2)|MCOND(FCONDO), IMMED|MCOND(~FCONDO)|FCC(~2)|F2(~2, ~0x58), "8,2,d", 0, v9 },
{ "movo",	F2(2, 0x58)|FCC(2)|MCOND(FCONDO)|IMMED, MCOND(~FCONDO)|FCC(~2)|F2(~2, ~0x58), "8,I,d", 0, v9 },
{ "movo",	F2(2, 0x58)|FCC(3)|MCOND(FCONDO), IMMED|MCOND(~FCONDO)|FCC(~3)|F2(~2, ~0x58), "9,2,d", 0, v9 },
{ "movo",	F2(2, 0x58)|FCC(3)|MCOND(FCONDO)|IMMED, MCOND(~FCONDO)|FCC(~3)|F2(~2, ~0x58), "9,I,d", 0, v9 },
{ "movpos",	F2(2, 0x59)|MCOND(CONDPOS)|ICC, F2(~2, ~0x59)|MCOND(~CONDPOS)|IMMED|XCC|(1<<12), "z,2,d", 0, v9 },
{ "movpos",	F2(2, 0x59)|MCOND(CONDPOS)|ICC|IMMED, F2(~2, ~0x59)|MCOND(~CONDPOS)|XCC|(1<<12), "z,I,d", 0, v9 },
{ "movpos",	F2(2, 0x59)|MCOND(CONDPOS)|XCC, F2(~2, ~0x59)|MCOND(~CONDPOS)|IMMED|(1<<12), "Z,2,d", 0, v9 },
{ "movpos",	F2(2, 0x59)|MCOND(CONDPOS)|XCC|IMMED, F2(~2, ~0x59)|MCOND(~CONDPOS)|(1<<12), "Z,I,d", 0, v9 },
{ "movu",	F2(2, 0x58)|FCC(0)|MCOND(FCONDU), IMMED|MCOND(~FCONDU)|FCC(~0)|F2(~2, ~0x58), "6,2,d", 0, v9 },
{ "movu",	F2(2, 0x58)|FCC(0)|MCOND(FCONDU)|IMMED, MCOND(~FCONDU)|FCC(~0)|F2(~2, ~0x58), "6,I,d", 0, v9 },
{ "movu",	F2(2, 0x58)|FCC(1)|MCOND(FCONDU), IMMED|MCOND(~FCONDU)|FCC(~1)|F2(~2, ~0x58), "7,2,d", 0, v9 },
{ "movu",	F2(2, 0x58)|FCC(1)|MCOND(FCONDU)|IMMED, MCOND(~FCONDU)|FCC(~1)|F2(~2, ~0x58), "7,I,d", 0, v9 },
{ "movu",	F2(2, 0x58)|FCC(2)|MCOND(FCONDU), IMMED|MCOND(~FCONDU)|FCC(~2)|F2(~2, ~0x58), "8,2,d", 0, v9 },
{ "movu",	F2(2, 0x58)|FCC(2)|MCOND(FCONDU)|IMMED, MCOND(~FCONDU)|FCC(~2)|F2(~2, ~0x58), "8,I,d", 0, v9 },
{ "movu",	F2(2, 0x58)|FCC(3)|MCOND(FCONDU), IMMED|MCOND(~FCONDU)|FCC(~3)|F2(~2, ~0x58), "9,2,d", 0, v9 },
{ "movu",	F2(2, 0x58)|FCC(3)|MCOND(FCONDU)|IMMED, MCOND(~FCONDU)|FCC(~3)|F2(~2, ~0x58), "9,I,d", 0, v9 },
{ "movue",	F2(2, 0x58)|FCC(0)|MCOND(FCONDUE), IMMED|MCOND(~FCONDUE)|FCC(~0)|F2(~2, ~0x58), "6,2,d", 0, v9 },
{ "movue",	F2(2, 0x58)|FCC(0)|MCOND(FCONDUE)|IMMED, MCOND(~FCONDUE)|FCC(~0)|F2(~2, ~0x58), "6,I,d", 0, v9 },
{ "movue",	F2(2, 0x58)|FCC(1)|MCOND(FCONDUE), IMMED|MCOND(~FCONDUE)|FCC(~1)|F2(~2, ~0x58), "7,2,d", 0, v9 },
{ "movue",	F2(2, 0x58)|FCC(1)|MCOND(FCONDUE)|IMMED, MCOND(~FCONDUE)|FCC(~1)|F2(~2, ~0x58), "7,I,d", 0, v9 },
{ "movue",	F2(2, 0x58)|FCC(2)|MCOND(FCONDUE), IMMED|MCOND(~FCONDUE)|FCC(~2)|F2(~2, ~0x58), "8,2,d", 0, v9 },
{ "movue",	F2(2, 0x58)|FCC(2)|MCOND(FCONDUE)|IMMED, MCOND(~FCONDUE)|FCC(~2)|F2(~2, ~0x58), "8,I,d", 0, v9 },
{ "movue",	F2(2, 0x58)|FCC(3)|MCOND(FCONDUE), IMMED|MCOND(~FCONDUE)|FCC(~3)|F2(~2, ~0x58), "9,2,d", 0, v9 },
{ "movue",	F2(2, 0x58)|FCC(3)|MCOND(FCONDUE)|IMMED, MCOND(~FCONDUE)|FCC(~3)|F2(~2, ~0x58), "9,I,d", 0, v9 },
{ "movug",	F2(2, 0x58)|FCC(0)|MCOND(FCONDUG), IMMED|MCOND(~FCONDUG)|FCC(~0)|F2(~2, ~0x58), "6,2,d", 0, v9 },
{ "movug",	F2(2, 0x58)|FCC(0)|MCOND(FCONDUG)|IMMED, MCOND(~FCONDUG)|FCC(~0)|F2(~2, ~0x58), "6,I,d", 0, v9 },
{ "movug",	F2(2, 0x58)|FCC(1)|MCOND(FCONDUG), IMMED|MCOND(~FCONDUG)|FCC(~1)|F2(~2, ~0x58), "7,2,d", 0, v9 },
{ "movug",	F2(2, 0x58)|FCC(1)|MCOND(FCONDUG)|IMMED, MCOND(~FCONDUG)|FCC(~1)|F2(~2, ~0x58), "7,I,d", 0, v9 },
{ "movug",	F2(2, 0x58)|FCC(2)|MCOND(FCONDUG), IMMED|MCOND(~FCONDUG)|FCC(~2)|F2(~2, ~0x58), "8,2,d", 0, v9 },
{ "movug",	F2(2, 0x58)|FCC(2)|MCOND(FCONDUG)|IMMED, MCOND(~FCONDUG)|FCC(~2)|F2(~2, ~0x58), "8,I,d", 0, v9 },
{ "movug",	F2(2, 0x58)|FCC(3)|MCOND(FCONDUG), IMMED|MCOND(~FCONDUG)|FCC(~3)|F2(~2, ~0x58), "9,2,d", 0, v9 },
{ "movug",	F2(2, 0x58)|FCC(3)|MCOND(FCONDUG)|IMMED, MCOND(~FCONDUG)|FCC(~3)|F2(~2, ~0x58), "9,I,d", 0, v9 },
{ "movuge",	F2(2, 0x58)|FCC(0)|MCOND(FCONDUGE), IMMED|MCOND(~FCONDUGE)|FCC(~0)|F2(~2, ~0x58), "6,2,d", 0, v9 },
{ "movuge",	F2(2, 0x58)|FCC(0)|MCOND(FCONDUGE)|IMMED, MCOND(~FCONDUGE)|FCC(~0)|F2(~2, ~0x58), "6,I,d", 0, v9 },
{ "movuge",	F2(2, 0x58)|FCC(1)|MCOND(FCONDUGE), IMMED|MCOND(~FCONDUGE)|FCC(~1)|F2(~2, ~0x58), "7,2,d", 0, v9 },
{ "movuge",	F2(2, 0x58)|FCC(1)|MCOND(FCONDUGE)|IMMED, MCOND(~FCONDUGE)|FCC(~1)|F2(~2, ~0x58), "7,I,d", 0, v9 },
{ "movuge",	F2(2, 0x58)|FCC(2)|MCOND(FCONDUGE), IMMED|MCOND(~FCONDUGE)|FCC(~2)|F2(~2, ~0x58), "8,2,d", 0, v9 },
{ "movuge",	F2(2, 0x58)|FCC(2)|MCOND(FCONDUGE)|IMMED, MCOND(~FCONDUGE)|FCC(~2)|F2(~2, ~0x58), "8,I,d", 0, v9 },
{ "movuge",	F2(2, 0x58)|FCC(3)|MCOND(FCONDUGE), IMMED|MCOND(~FCONDUGE)|FCC(~3)|F2(~2, ~0x58), "9,2,d", 0, v9 },
{ "movuge",	F2(2, 0x58)|FCC(3)|MCOND(FCONDUGE)|IMMED, MCOND(~FCONDUGE)|FCC(~3)|F2(~2, ~0x58), "9,I,d", 0, v9 },
{ "movul",	F2(2, 0x58)|FCC(0)|MCOND(FCONDUL), IMMED|MCOND(~FCONDUL)|FCC(~0)|F2(~2, ~0x58), "6,2,d", 0, v9 },
{ "movul",	F2(2, 0x58)|FCC(0)|MCOND(FCONDUL)|IMMED, MCOND(~FCONDUL)|FCC(~0)|F2(~2, ~0x58), "6,I,d", 0, v9 },
{ "movul",	F2(2, 0x58)|FCC(1)|MCOND(FCONDUL), IMMED|MCOND(~FCONDUL)|FCC(~1)|F2(~2, ~0x58), "7,2,d", 0, v9 },
{ "movul",	F2(2, 0x58)|FCC(1)|MCOND(FCONDUL)|IMMED, MCOND(~FCONDUL)|FCC(~1)|F2(~2, ~0x58), "7,I,d", 0, v9 },
{ "movul",	F2(2, 0x58)|FCC(2)|MCOND(FCONDUL), IMMED|MCOND(~FCONDUL)|FCC(~2)|F2(~2, ~0x58), "8,2,d", 0, v9 },
{ "movul",	F2(2, 0x58)|FCC(2)|MCOND(FCONDUL)|IMMED, MCOND(~FCONDUL)|FCC(~2)|F2(~2, ~0x58), "8,I,d", 0, v9 },
{ "movul",	F2(2, 0x58)|FCC(3)|MCOND(FCONDUL), IMMED|MCOND(~FCONDUL)|FCC(~3)|F2(~2, ~0x58), "9,2,d", 0, v9 },
{ "movul",	F2(2, 0x58)|FCC(3)|MCOND(FCONDUL)|IMMED, MCOND(~FCONDUL)|FCC(~3)|F2(~2, ~0x58), "9,I,d", 0, v9 },
{ "movule",	F2(2, 0x58)|FCC(0)|MCOND(FCONDULE), IMMED|MCOND(~FCONDULE)|FCC(~0)|F2(~2, ~0x58), "6,2,d", 0, v9 },
{ "movule",	F2(2, 0x58)|FCC(0)|MCOND(FCONDULE)|IMMED, MCOND(~FCONDULE)|FCC(~0)|F2(~2, ~0x58), "6,I,d", 0, v9 },
{ "movule",	F2(2, 0x58)|FCC(1)|MCOND(FCONDULE), IMMED|MCOND(~FCONDULE)|FCC(~1)|F2(~2, ~0x58), "7,2,d", 0, v9 },
{ "movule",	F2(2, 0x58)|FCC(1)|MCOND(FCONDULE)|IMMED, MCOND(~FCONDULE)|FCC(~1)|F2(~2, ~0x58), "7,I,d", 0, v9 },
{ "movule",	F2(2, 0x58)|FCC(2)|MCOND(FCONDULE), IMMED|MCOND(~FCONDULE)|FCC(~2)|F2(~2, ~0x58), "8,2,d", 0, v9 },
{ "movule",	F2(2, 0x58)|FCC(2)|MCOND(FCONDULE)|IMMED, MCOND(~FCONDULE)|FCC(~2)|F2(~2, ~0x58), "8,I,d", 0, v9 },
{ "movule",	F2(2, 0x58)|FCC(3)|MCOND(FCONDULE), IMMED|MCOND(~FCONDULE)|FCC(~3)|F2(~2, ~0x58), "9,2,d", 0, v9 },
{ "movule",	F2(2, 0x58)|FCC(3)|MCOND(FCONDULE)|IMMED, MCOND(~FCONDULE)|FCC(~3)|F2(~2, ~0x58), "9,I,d", 0, v9 },
{ "movvc",	F2(2, 0x59)|MCOND(CONDVC)|ICC, F2(~2, ~0x59)|MCOND(~CONDVC)|IMMED|XCC|(1<<12), "z,2,d", 0, v9 },
{ "movvc",	F2(2, 0x59)|MCOND(CONDVC)|ICC|IMMED, F2(~2, ~0x59)|MCOND(~CONDVC)|XCC|(1<<12), "z,I,d", 0, v9 },
{ "movvc",	F2(2, 0x59)|MCOND(CONDVC)|XCC, F2(~2, ~0x59)|MCOND(~CONDVC)|IMMED|(1<<12), "Z,2,d", 0, v9 },
{ "movvc",	F2(2, 0x59)|MCOND(CONDVC)|XCC|IMMED, F2(~2, ~0x59)|MCOND(~CONDVC)|(1<<12), "Z,I,d", 0, v9 },
{ "movvs",	F2(2, 0x59)|MCOND(CONDVS)|ICC, F2(~2, ~0x59)|MCOND(~CONDVS)|IMMED|XCC|(1<<12), "z,2,d", 0, v9 },
{ "movvs",	F2(2, 0x59)|MCOND(CONDVS)|ICC|IMMED, F2(~2, ~0x59)|MCOND(~CONDVS)|XCC|(1<<12), "z,I,d", 0, v9 },
{ "movvs",	F2(2, 0x59)|MCOND(CONDVS)|XCC, F2(~2, ~0x59)|MCOND(~CONDVS)|IMMED|(1<<12), "Z,2,d", 0, v9 },
{ "movvs",	F2(2, 0x59)|MCOND(CONDVS)|XCC|IMMED, F2(~2, ~0x59)|MCOND(~CONDVS)|(1<<12), "Z,I,d", 0, v9 },
{ "movz",	F2(2, 0x58)|FCC(0)|MCOND(FCONDZ), IMMED|MCOND(~FCONDZ)|FCC(~0)|F2(~2, ~0x58), "6,2,d", 0, v9 },
{ "movz",	F2(2, 0x58)|FCC(0)|MCOND(FCONDZ)|IMMED, MCOND(~FCONDZ)|FCC(~0)|F2(~2, ~0x58), "6,I,d", 0, v9 },
{ "movz",	F2(2, 0x58)|FCC(1)|MCOND(FCONDZ), IMMED|MCOND(~FCONDZ)|FCC(~1)|F2(~2, ~0x58), "7,2,d", 0, v9 },
{ "movz",	F2(2, 0x58)|FCC(1)|MCOND(FCONDZ)|IMMED, MCOND(~FCONDZ)|FCC(~1)|F2(~2, ~0x58), "7,I,d", 0, v9 },
{ "movz",	F2(2, 0x58)|FCC(2)|MCOND(FCONDZ), IMMED|MCOND(~FCONDZ)|FCC(~2)|F2(~2, ~0x58), "8,2,d", 0, v9 },
{ "movz",	F2(2, 0x58)|FCC(2)|MCOND(FCONDZ)|IMMED, MCOND(~FCONDZ)|FCC(~2)|F2(~2, ~0x58), "8,I,d", 0, v9 },
{ "movz",	F2(2, 0x58)|FCC(3)|MCOND(FCONDZ), IMMED|MCOND(~FCONDZ)|FCC(~3)|F2(~2, ~0x58), "9,2,d", 0, v9 },
{ "movz",	F2(2, 0x58)|FCC(3)|MCOND(FCONDZ)|IMMED, MCOND(~FCONDZ)|FCC(~3)|F2(~2, ~0x58), "9,I,d", 0, v9 },

{ "fmovad",	F3F(2, 0x35, 0x082)|(1<<18)|MCOND(CONDA),  F3F(~2, ~0x35, ~0x082)|MCOND(~CONDA),	"z,f,g", 0, v9 },
{ "fmovad",	F3F(2, 0x35, 0x082)|MCOND(FCONDA), (1<<18)|F3F(~2, ~0x35, ~0x082)|MCOND(~FCONDA),	"6,f,g", 0, v9 },
{ "fmovad",	F3F(2, 0x35, 0x0a2)|(1<<18)|MCOND(CONDA),  F3F(~2, ~0x35, ~0x0a2)|MCOND(~CONDA),	"Z,f,g", 0, v9 },
{ "fmovad",	F3F(2, 0x35, 0x0a2)|MCOND(FCONDA), (1<<18)|F3F(~2, ~0x35, ~0x0a2)|MCOND(~FCONDA),	"7,f,g", 0, v9 },
{ "fmovad",	F3F(2, 0x35, 0x0c2)|MCOND(FCONDA), (1<<18)|F3F(~2, ~0x35, ~0x0c2)|MCOND(~FCONDA),	"8,f,g", 0, v9 },
{ "fmovad",	F3F(2, 0x35, 0x0e2)|MCOND(FCONDA), (1<<18)|F3F(~2, ~0x35, ~0x0e2)|MCOND(~FCONDA),	"9,f,g", 0, v9 },
{ "fmovaq",	F3F(2, 0x35, 0x083)|(1<<18)|MCOND(CONDA),  F3F(~2, ~0x35, ~0x083)|MCOND(~CONDA),	"z,f,g", 0, v9 },
{ "fmovaq",	F3F(2, 0x35, 0x083)|MCOND(FCONDA), (1<<18)|F3F(~2, ~0x35, ~0x083)|MCOND(~FCONDA),	"6,f,g", 0, v9 },
{ "fmovaq",	F3F(2, 0x35, 0x0a3)|(1<<18)|MCOND(CONDA),  F3F(~2, ~0x35, ~0x0a3)|MCOND(~CONDA),	"Z,f,g", 0, v9 },
{ "fmovaq",	F3F(2, 0x35, 0x0a3)|MCOND(FCONDA), (1<<18)|F3F(~2, ~0x35, ~0x0a3)|MCOND(~FCONDA),	"7,f,g", 0, v9 },
{ "fmovaq",	F3F(2, 0x35, 0x0c3)|MCOND(FCONDA), (1<<18)|F3F(~2, ~0x35, ~0x0c3)|MCOND(~FCONDA),	"8,f,g", 0, v9 },
{ "fmovaq",	F3F(2, 0x35, 0x0e3)|MCOND(FCONDA), (1<<18)|F3F(~2, ~0x35, ~0x0e3)|MCOND(~FCONDA),	"9,f,g", 0, v9 },
{ "fmovas",	F3F(2, 0x35, 0x081)|(1<<18)|MCOND(CONDA),  F3F(~2, ~0x35, ~0x081)|MCOND(~CONDA),	"z,f,g", 0, v9 },
{ "fmovas",	F3F(2, 0x35, 0x081)|MCOND(FCONDA), (1<<18)|F3F(~2, ~0x35, ~0x081)|MCOND(~FCONDA),	"6,f,g", 0, v9 },
{ "fmovas",	F3F(2, 0x35, 0x0a1)|(1<<18)|MCOND(CONDA),  F3F(~2, ~0x35, ~0x0a1)|MCOND(~CONDA),	"Z,f,g", 0, v9 },
{ "fmovas",	F3F(2, 0x35, 0x0a1)|MCOND(FCONDA), (1<<18)|F3F(~2, ~0x35, ~0x0a1)|MCOND(~FCONDA),	"7,f,g", 0, v9 },
{ "fmovas",	F3F(2, 0x35, 0x0c1)|MCOND(FCONDA), (1<<18)|F3F(~2, ~0x35, ~0x0c1)|MCOND(~FCONDA),	"8,f,g", 0, v9 },
{ "fmovas",	F3F(2, 0x35, 0x0e1)|MCOND(FCONDA), (1<<18)|F3F(~2, ~0x35, ~0x0e1)|MCOND(~FCONDA),	"9,f,g", 0, v9 },
{ "fmovccd",	F3F(2, 0x35, 0x082)|(1<<18)|MCOND(CONDCC), F3F(~2, ~0x35, ~0x082)|MCOND(~CONDCC),	"z,f,g", 0, v9 },
{ "fmovccd",	F3F(2, 0x35, 0x0a2)|(1<<18)|MCOND(CONDCC), F3F(~2, ~0x35, ~0x0a2)|MCOND(~CONDCC),	"Z,f,g", 0, v9 },
{ "fmovccq",	F3F(2, 0x35, 0x083)|(1<<18)|MCOND(CONDCC), F3F(~2, ~0x35, ~0x083)|MCOND(~CONDCC),	"z,f,g", 0, v9 },
{ "fmovccq",	F3F(2, 0x35, 0x0a3)|(1<<18)|MCOND(CONDCC), F3F(~2, ~0x35, ~0x0a3)|MCOND(~CONDCC),	"Z,f,g", 0, v9 },
{ "fmovccs",	F3F(2, 0x35, 0x081)|(1<<18)|MCOND(CONDCC), F3F(~2, ~0x35, ~0x081)|MCOND(~CONDCC),	"z,f,g", 0, v9 },
{ "fmovccs",	F3F(2, 0x35, 0x0a1)|(1<<18)|MCOND(CONDCC), F3F(~2, ~0x35, ~0x0a1)|MCOND(~CONDCC),	"Z,f,g", 0, v9 },
{ "fmovcsd",	F3F(2, 0x35, 0x082)|(1<<18)|MCOND(CONDCS), F3F(~2, ~0x35, ~0x082)|MCOND(~CONDCS),	"z,f,g", 0, v9 },
{ "fmovcsd",	F3F(2, 0x35, 0x0a2)|(1<<18)|MCOND(CONDCS), F3F(~2, ~0x35, ~0x0a2)|MCOND(~CONDCS),	"Z,f,g", 0, v9 },
{ "fmovcsq",	F3F(2, 0x35, 0x083)|(1<<18)|MCOND(CONDCS), F3F(~2, ~0x35, ~0x083)|MCOND(~CONDCS),	"z,f,g", 0, v9 },
{ "fmovcsq",	F3F(2, 0x35, 0x0a3)|(1<<18)|MCOND(CONDCS), F3F(~2, ~0x35, ~0x0a3)|MCOND(~CONDCS),	"Z,f,g", 0, v9 },
{ "fmovcss",	F3F(2, 0x35, 0x081)|(1<<18)|MCOND(CONDCS), F3F(~2, ~0x35, ~0x081)|MCOND(~CONDCS),	"z,f,g", 0, v9 },
{ "fmovcss",	F3F(2, 0x35, 0x0a1)|(1<<18)|MCOND(CONDCS), F3F(~2, ~0x35, ~0x0a1)|MCOND(~CONDCS),	"Z,f,g", 0, v9 },
{ "fmoved",	F3F(2, 0x35, 0x082)|(1<<18)|MCOND(CONDE),  F3F(~2, ~0x35, ~0x082)|MCOND(~CONDE),	"z,f,g", 0, v9 },
{ "fmoved",	F3F(2, 0x35, 0x082)|MCOND(FCONDE), (1<<18)|F3F(~2, ~0x35, ~0x082)|MCOND(~FCONDE),	"6,f,g", 0, v9 },
{ "fmoved",	F3F(2, 0x35, 0x0a2)|(1<<18)|MCOND(CONDE),  F3F(~2, ~0x35, ~0x0a2)|MCOND(~CONDE),	"Z,f,g", 0, v9 },
{ "fmoved",	F3F(2, 0x35, 0x0a2)|MCOND(FCONDE), (1<<18)|F3F(~2, ~0x35, ~0x0a2)|MCOND(~FCONDE),	"7,f,g", 0, v9 },
{ "fmoved",	F3F(2, 0x35, 0x0c2)|MCOND(FCONDE), (1<<18)|F3F(~2, ~0x35, ~0x0c2)|MCOND(~FCONDE),	"8,f,g", 0, v9 },
{ "fmoved",	F3F(2, 0x35, 0x0e2)|MCOND(FCONDE), (1<<18)|F3F(~2, ~0x35, ~0x0e2)|MCOND(~FCONDE),	"9,f,g", 0, v9 },
{ "fmoveq",	F3F(2, 0x35, 0x083)|(1<<18)|MCOND(CONDE),  F3F(~2, ~0x35, ~0x083)|MCOND(~CONDE),	"z,f,g", 0, v9 },
{ "fmoveq",	F3F(2, 0x35, 0x083)|MCOND(FCONDE), (1<<18)|F3F(~2, ~0x35, ~0x083)|MCOND(~FCONDE),	"6,f,g", 0, v9 },
{ "fmoveq",	F3F(2, 0x35, 0x0a3)|(1<<18)|MCOND(CONDE),  F3F(~2, ~0x35, ~0x0a3)|MCOND(~CONDE),	"Z,f,g", 0, v9 },
{ "fmoveq",	F3F(2, 0x35, 0x0a3)|MCOND(FCONDE), (1<<18)|F3F(~2, ~0x35, ~0x0a3)|MCOND(~FCONDE),	"7,f,g", 0, v9 },
{ "fmoveq",	F3F(2, 0x35, 0x0c3)|MCOND(FCONDE), (1<<18)|F3F(~2, ~0x35, ~0x0c3)|MCOND(~FCONDE),	"8,f,g", 0, v9 },
{ "fmoveq",	F3F(2, 0x35, 0x0e3)|MCOND(FCONDE), (1<<18)|F3F(~2, ~0x35, ~0x0e3)|MCOND(~FCONDE),	"9,f,g", 0, v9 },
{ "fmoves",	F3F(2, 0x35, 0x081)|(1<<18)|MCOND(CONDE),  F3F(~2, ~0x35, ~0x081)|MCOND(~CONDE),	"z,f,g", 0, v9 },
{ "fmoves",	F3F(2, 0x35, 0x081)|MCOND(FCONDE), (1<<18)|F3F(~2, ~0x35, ~0x081)|MCOND(~FCONDE),	"6,f,g", 0, v9 },
{ "fmoves",	F3F(2, 0x35, 0x0a1)|(1<<18)|MCOND(CONDE),  F3F(~2, ~0x35, ~0x0a1)|MCOND(~CONDE),	"Z,f,g", 0, v9 },
{ "fmoves",	F3F(2, 0x35, 0x0a1)|MCOND(FCONDE), (1<<18)|F3F(~2, ~0x35, ~0x0a1)|MCOND(~FCONDE),	"7,f,g", 0, v9 },
{ "fmoves",	F3F(2, 0x35, 0x0c1)|MCOND(FCONDE), (1<<18)|F3F(~2, ~0x35, ~0x0c1)|MCOND(~FCONDE),	"8,f,g", 0, v9 },
{ "fmoves",	F3F(2, 0x35, 0x0e1)|MCOND(FCONDE), (1<<18)|F3F(~2, ~0x35, ~0x0e1)|MCOND(~FCONDE),	"9,f,g", 0, v9 },
{ "fmovgd",	F3F(2, 0x35, 0x082)|(1<<18)|MCOND(CONDG),  F3F(~2, ~0x35, ~0x082)|MCOND(~CONDG),	"z,f,g", 0, v9 },
{ "fmovgd",	F3F(2, 0x35, 0x082)|MCOND(FCONDG), (1<<18)|F3F(~2, ~0x35, ~0x082)|MCOND(~FCONDG),	"6,f,g", 0, v9 },
{ "fmovgd",	F3F(2, 0x35, 0x0a2)|(1<<18)|MCOND(CONDG),  F3F(~2, ~0x35, ~0x0a2)|MCOND(~CONDG),	"Z,f,g", 0, v9 },
{ "fmovgd",	F3F(2, 0x35, 0x0a2)|MCOND(FCONDG), (1<<18)|F3F(~2, ~0x35, ~0x0a2)|MCOND(~FCONDG),	"7,f,g", 0, v9 },
{ "fmovgd",	F3F(2, 0x35, 0x0c2)|MCOND(FCONDG), (1<<18)|F3F(~2, ~0x35, ~0x0c2)|MCOND(~FCONDG),	"8,f,g", 0, v9 },
{ "fmovgd",	F3F(2, 0x35, 0x0e2)|MCOND(FCONDG), (1<<18)|F3F(~2, ~0x35, ~0x0e2)|MCOND(~FCONDG),	"9,f,g", 0, v9 },
{ "fmovged",	F3F(2, 0x35, 0x082)|(1<<18)|MCOND(CONDGE), F3F(~2, ~0x35, ~0x082)|MCOND(~CONDGE),	"z,f,g", 0, v9 },
{ "fmovged",	F3F(2, 0x35, 0x082)|MCOND(FCONDGE), (1<<18)|F3F(~2, ~0x35, ~0x082)|MCOND(~FCONDGE),	"6,f,g", 0, v9 },
{ "fmovged",	F3F(2, 0x35, 0x0a2)|(1<<18)|MCOND(CONDGE), F3F(~2, ~0x35, ~0x0a2)|MCOND(~CONDGE),	"Z,f,g", 0, v9 },
{ "fmovged",	F3F(2, 0x35, 0x0a2)|MCOND(FCONDGE), (1<<18)|F3F(~2, ~0x35, ~0x0a2)|MCOND(~FCONDGE),	"7,f,g", 0, v9 },
{ "fmovged",	F3F(2, 0x35, 0x0c2)|MCOND(FCONDGE), (1<<18)|F3F(~2, ~0x35, ~0x0c2)|MCOND(~FCONDGE),	"8,f,g", 0, v9 },
{ "fmovged",	F3F(2, 0x35, 0x0e2)|MCOND(FCONDGE), (1<<18)|F3F(~2, ~0x35, ~0x0e2)|MCOND(~FCONDGE),	"9,f,g", 0, v9 },
{ "fmovgeq",	F3F(2, 0x35, 0x083)|(1<<18)|MCOND(CONDGE), F3F(~2, ~0x35, ~0x083)|MCOND(~CONDGE),	"z,f,g", 0, v9 },
{ "fmovgeq",	F3F(2, 0x35, 0x083)|MCOND(FCONDGE), (1<<18)|F3F(~2, ~0x35, ~0x083)|MCOND(~FCONDGE),	"6,f,g", 0, v9 },
{ "fmovgeq",	F3F(2, 0x35, 0x0a3)|(1<<18)|MCOND(CONDGE), F3F(~2, ~0x35, ~0x0a3)|MCOND(~CONDGE),	"Z,f,g", 0, v9 },
{ "fmovgeq",	F3F(2, 0x35, 0x0a3)|MCOND(FCONDGE), (1<<18)|F3F(~2, ~0x35, ~0x0a3)|MCOND(~FCONDGE),	"7,f,g", 0, v9 },
{ "fmovgeq",	F3F(2, 0x35, 0x0c3)|MCOND(FCONDGE), (1<<18)|F3F(~2, ~0x35, ~0x0c3)|MCOND(~FCONDGE),	"8,f,g", 0, v9 },
{ "fmovgeq",	F3F(2, 0x35, 0x0e3)|MCOND(FCONDGE), (1<<18)|F3F(~2, ~0x35, ~0x0e3)|MCOND(~FCONDGE),	"9,f,g", 0, v9 },
{ "fmovges",	F3F(2, 0x35, 0x081)|(1<<18)|MCOND(CONDGE), F3F(~2, ~0x35, ~0x081)|MCOND(~CONDGE),	"z,f,g", 0, v9 },
{ "fmovges",	F3F(2, 0x35, 0x081)|MCOND(FCONDGE), (1<<18)|F3F(~2, ~0x35, ~0x081)|MCOND(~FCONDGE),	"6,f,g", 0, v9 },
{ "fmovges",	F3F(2, 0x35, 0x0a1)|(1<<18)|MCOND(CONDGE), F3F(~2, ~0x35, ~0x0a1)|MCOND(~CONDGE),	"Z,f,g", 0, v9 },
{ "fmovges",	F3F(2, 0x35, 0x0a1)|MCOND(FCONDGE), (1<<18)|F3F(~2, ~0x35, ~0x0a1)|MCOND(~FCONDGE),	"7,f,g", 0, v9 },
{ "fmovges",	F3F(2, 0x35, 0x0c1)|MCOND(FCONDGE), (1<<18)|F3F(~2, ~0x35, ~0x0c1)|MCOND(~FCONDGE),	"8,f,g", 0, v9 },
{ "fmovges",	F3F(2, 0x35, 0x0e1)|MCOND(FCONDGE), (1<<18)|F3F(~2, ~0x35, ~0x0e1)|MCOND(~FCONDGE),	"9,f,g", 0, v9 },
{ "fmovgeud",	F3F(2, 0x35, 0x082)|(1<<18)|MCOND(CONDGEU), F3F(~2, ~0x35, ~0x082)|MCOND(~CONDGEU),	"z,f,g", F_ALIAS, v9 },
{ "fmovgeud",	F3F(2, 0x35, 0x0a2)|(1<<18)|MCOND(CONDGEU), F3F(~2, ~0x35, ~0x0a2)|MCOND(~CONDGEU),	"Z,f,g", F_ALIAS, v9 },
{ "fmovgeuq",	F3F(2, 0x35, 0x083)|(1<<18)|MCOND(CONDGEU), F3F(~2, ~0x35, ~0x083)|MCOND(~CONDGEU),	"z,f,g", F_ALIAS, v9 },
{ "fmovgeuq",	F3F(2, 0x35, 0x0a3)|(1<<18)|MCOND(CONDGEU), F3F(~2, ~0x35, ~0x0a3)|MCOND(~CONDGEU),	"Z,f,g", F_ALIAS, v9 },
{ "fmovgeus",	F3F(2, 0x35, 0x081)|(1<<18)|MCOND(CONDGEU), F3F(~2, ~0x35, ~0x081)|MCOND(~CONDGEU),	"z,f,g", F_ALIAS, v9 },
{ "fmovgeus",	F3F(2, 0x35, 0x0a1)|(1<<18)|MCOND(CONDGEU), F3F(~2, ~0x35, ~0x0a1)|MCOND(~CONDGEU),	"Z,f,g", F_ALIAS, v9 },
{ "fmovgq",	F3F(2, 0x35, 0x083)|(1<<18)|MCOND(CONDG),  F3F(~2, ~0x35, ~0x083)|MCOND(~CONDG),	"z,f,g", 0, v9 },
{ "fmovgq",	F3F(2, 0x35, 0x083)|MCOND(FCONDG), (1<<18)|F3F(~2, ~0x35, ~0x083)|MCOND(~FCONDG),	"6,f,g", 0, v9 },
{ "fmovgq",	F3F(2, 0x35, 0x0a3)|(1<<18)|MCOND(CONDG),  F3F(~2, ~0x35, ~0x0a3)|MCOND(~CONDG),	"Z,f,g", 0, v9 },
{ "fmovgq",	F3F(2, 0x35, 0x0a3)|MCOND(FCONDG), (1<<18)|F3F(~2, ~0x35, ~0x0a3)|MCOND(~FCONDG),	"7,f,g", 0, v9 },
{ "fmovgq",	F3F(2, 0x35, 0x0c3)|MCOND(FCONDG), (1<<18)|F3F(~2, ~0x35, ~0x0c3)|MCOND(~FCONDG),	"8,f,g", 0, v9 },
{ "fmovgq",	F3F(2, 0x35, 0x0e3)|MCOND(FCONDG), (1<<18)|F3F(~2, ~0x35, ~0x0e3)|MCOND(~FCONDG),	"9,f,g", 0, v9 },
{ "fmovgs",	F3F(2, 0x35, 0x081)|(1<<18)|MCOND(CONDG),  F3F(~2, ~0x35, ~0x081)|MCOND(~CONDG),	"z,f,g", 0, v9 },
{ "fmovgs",	F3F(2, 0x35, 0x081)|MCOND(FCONDG), (1<<18)|F3F(~2, ~0x35, ~0x081)|MCOND(~FCONDG),	"6,f,g", 0, v9 },
{ "fmovgs",	F3F(2, 0x35, 0x0a1)|(1<<18)|MCOND(CONDG),  F3F(~2, ~0x35, ~0x0a1)|MCOND(~CONDG),	"Z,f,g", 0, v9 },
{ "fmovgs",	F3F(2, 0x35, 0x0a1)|MCOND(FCONDG), (1<<18)|F3F(~2, ~0x35, ~0x0a1)|MCOND(~FCONDG),	"7,f,g", 0, v9 },
{ "fmovgs",	F3F(2, 0x35, 0x0c1)|MCOND(FCONDG), (1<<18)|F3F(~2, ~0x35, ~0x0c1)|MCOND(~FCONDG),	"8,f,g", 0, v9 },
{ "fmovgs",	F3F(2, 0x35, 0x0e1)|MCOND(FCONDG), (1<<18)|F3F(~2, ~0x35, ~0x0e1)|MCOND(~FCONDG),	"9,f,g", 0, v9 },
{ "fmovgud",	F3F(2, 0x35, 0x082)|(1<<18)|MCOND(CONDGU), F3F(~2, ~0x35, ~0x082)|MCOND(~CONDGU),	"z,f,g", 0, v9 },
{ "fmovgud",	F3F(2, 0x35, 0x0a2)|(1<<18)|MCOND(CONDGU), F3F(~2, ~0x35, ~0x0a2)|MCOND(~CONDGU),	"Z,f,g", 0, v9 },
{ "fmovguq",	F3F(2, 0x35, 0x083)|(1<<18)|MCOND(CONDGU), F3F(~2, ~0x35, ~0x083)|MCOND(~CONDGU),	"z,f,g", 0, v9 },
{ "fmovguq",	F3F(2, 0x35, 0x0a3)|(1<<18)|MCOND(CONDGU), F3F(~2, ~0x35, ~0x0a3)|MCOND(~CONDGU),	"Z,f,g", 0, v9 },
{ "fmovgus",	F3F(2, 0x35, 0x081)|(1<<18)|MCOND(CONDGU), F3F(~2, ~0x35, ~0x081)|MCOND(~CONDGU),	"z,f,g", 0, v9 },
{ "fmovgus",	F3F(2, 0x35, 0x0a1)|(1<<18)|MCOND(CONDGU), F3F(~2, ~0x35, ~0x0a1)|MCOND(~CONDGU),	"Z,f,g", 0, v9 },
{ "fmovld",	F3F(2, 0x35, 0x082)|(1<<18)|MCOND(CONDL),  F3F(~2, ~0x35, ~0x082)|MCOND(~CONDL),	"z,f,g", 0, v9 },
{ "fmovld",	F3F(2, 0x35, 0x082)|MCOND(FCONDL), (1<<18)|F3F(~2, ~0x35, ~0x082)|MCOND(~FCONDL),	"6,f,g", 0, v9 },
{ "fmovld",	F3F(2, 0x35, 0x0a2)|(1<<18)|MCOND(CONDL),  F3F(~2, ~0x35, ~0x0a2)|MCOND(~CONDL),	"Z,f,g", 0, v9 },
{ "fmovld",	F3F(2, 0x35, 0x0a2)|MCOND(FCONDL), (1<<18)|F3F(~2, ~0x35, ~0x0a2)|MCOND(~FCONDL),	"7,f,g", 0, v9 },
{ "fmovld",	F3F(2, 0x35, 0x0c2)|MCOND(FCONDL), (1<<18)|F3F(~2, ~0x35, ~0x0c2)|MCOND(~FCONDL),	"8,f,g", 0, v9 },
{ "fmovld",	F3F(2, 0x35, 0x0e2)|MCOND(FCONDL), (1<<18)|F3F(~2, ~0x35, ~0x0e2)|MCOND(~FCONDL),	"9,f,g", 0, v9 },
{ "fmovled",	F3F(2, 0x35, 0x082)|(1<<18)|MCOND(CONDLE), F3F(~2, ~0x35, ~0x082)|MCOND(~CONDLE),	"z,f,g", 0, v9 },
{ "fmovled",	F3F(2, 0x35, 0x082)|MCOND(FCONDLE), (1<<18)|F3F(~2, ~0x35, ~0x082)|MCOND(~FCONDLE),	"6,f,g", 0, v9 },
{ "fmovled",	F3F(2, 0x35, 0x0a2)|(1<<18)|MCOND(CONDLE), F3F(~2, ~0x35, ~0x0a2)|MCOND(~CONDLE),	"Z,f,g", 0, v9 },
{ "fmovled",	F3F(2, 0x35, 0x0a2)|MCOND(FCONDLE), (1<<18)|F3F(~2, ~0x35, ~0x0a2)|MCOND(~FCONDLE),	"7,f,g", 0, v9 },
{ "fmovled",	F3F(2, 0x35, 0x0c2)|MCOND(FCONDLE), (1<<18)|F3F(~2, ~0x35, ~0x0c2)|MCOND(~FCONDLE),	"8,f,g", 0, v9 },
{ "fmovled",	F3F(2, 0x35, 0x0e2)|MCOND(FCONDLE), (1<<18)|F3F(~2, ~0x35, ~0x0e2)|MCOND(~FCONDLE),	"9,f,g", 0, v9 },
{ "fmovleq",	F3F(2, 0x35, 0x083)|(1<<18)|MCOND(CONDLE), F3F(~2, ~0x35, ~0x083)|MCOND(~CONDLE),	"z,f,g", 0, v9 },
{ "fmovleq",	F3F(2, 0x35, 0x083)|MCOND(FCONDLE), (1<<18)|F3F(~2, ~0x35, ~0x083)|MCOND(~FCONDLE),	"6,f,g", 0, v9 },
{ "fmovleq",	F3F(2, 0x35, 0x0a3)|(1<<18)|MCOND(CONDLE), F3F(~2, ~0x35, ~0x0a3)|MCOND(~CONDLE),	"Z,f,g", 0, v9 },
{ "fmovleq",	F3F(2, 0x35, 0x0a3)|MCOND(FCONDLE), (1<<18)|F3F(~2, ~0x35, ~0x0a3)|MCOND(~FCONDLE),	"7,f,g", 0, v9 },
{ "fmovleq",	F3F(2, 0x35, 0x0c3)|MCOND(FCONDLE), (1<<18)|F3F(~2, ~0x35, ~0x0c3)|MCOND(~FCONDLE),	"8,f,g", 0, v9 },
{ "fmovleq",	F3F(2, 0x35, 0x0e3)|MCOND(FCONDLE), (1<<18)|F3F(~2, ~0x35, ~0x0e3)|MCOND(~FCONDLE),	"9,f,g", 0, v9 },
{ "fmovles",	F3F(2, 0x35, 0x081)|(1<<18)|MCOND(CONDLE), F3F(~2, ~0x35, ~0x081)|MCOND(~CONDLE),	"z,f,g", 0, v9 },
{ "fmovles",	F3F(2, 0x35, 0x081)|MCOND(FCONDLE), (1<<18)|F3F(~2, ~0x35, ~0x081)|MCOND(~FCONDLE),	"6,f,g", 0, v9 },
{ "fmovles",	F3F(2, 0x35, 0x0a1)|(1<<18)|MCOND(CONDLE), F3F(~2, ~0x35, ~0x0a1)|MCOND(~CONDLE),	"Z,f,g", 0, v9 },
{ "fmovles",	F3F(2, 0x35, 0x0a1)|MCOND(FCONDLE), (1<<18)|F3F(~2, ~0x35, ~0x0a1)|MCOND(~FCONDLE),	"7,f,g", 0, v9 },
{ "fmovles",	F3F(2, 0x35, 0x0c1)|MCOND(FCONDLE), (1<<18)|F3F(~2, ~0x35, ~0x0c1)|MCOND(~FCONDLE),	"8,f,g", 0, v9 },
{ "fmovles",	F3F(2, 0x35, 0x0e1)|MCOND(FCONDLE), (1<<18)|F3F(~2, ~0x35, ~0x0e1)|MCOND(~FCONDLE),	"9,f,g", 0, v9 },
{ "fmovleud",	F3F(2, 0x35, 0x082)|(1<<18)|MCOND(CONDLEU), F3F(~2, ~0x35, ~0x082)|MCOND(~CONDLEU),	"z,f,g", 0, v9 },
{ "fmovleud",	F3F(2, 0x35, 0x0a2)|(1<<18)|MCOND(CONDLEU), F3F(~2, ~0x35, ~0x0a2)|MCOND(~CONDLEU),	"Z,f,g", 0, v9 },
{ "fmovleuq",	F3F(2, 0x35, 0x083)|(1<<18)|MCOND(CONDLEU), F3F(~2, ~0x35, ~0x083)|MCOND(~CONDLEU),	"z,f,g", 0, v9 },
{ "fmovleuq",	F3F(2, 0x35, 0x0a3)|(1<<18)|MCOND(CONDLEU), F3F(~2, ~0x35, ~0x0a3)|MCOND(~CONDLEU),	"Z,f,g", 0, v9 },
{ "fmovleus",	F3F(2, 0x35, 0x081)|(1<<18)|MCOND(CONDLEU), F3F(~2, ~0x35, ~0x081)|MCOND(~CONDLEU),	"z,f,g", 0, v9 },
{ "fmovleus",	F3F(2, 0x35, 0x0a1)|(1<<18)|MCOND(CONDLEU), F3F(~2, ~0x35, ~0x0a1)|MCOND(~CONDLEU),	"Z,f,g", 0, v9 },
{ "fmovlgd",	F3F(2, 0x35, 0x082)|MCOND(FCONDLG), (1<<18)|F3F(~2, ~0x35, ~0x082)|MCOND(~FCONDLG),	"6,f,g", 0, v9 },
{ "fmovlgd",	F3F(2, 0x35, 0x0a2)|MCOND(FCONDLG), (1<<18)|F3F(~2, ~0x35, ~0x0a2)|MCOND(~FCONDLG),	"7,f,g", 0, v9 },
{ "fmovlgd",	F3F(2, 0x35, 0x0c2)|MCOND(FCONDLG), (1<<18)|F3F(~2, ~0x35, ~0x0c2)|MCOND(~FCONDLG),	"8,f,g", 0, v9 },
{ "fmovlgd",	F3F(2, 0x35, 0x0e2)|MCOND(FCONDLG), (1<<18)|F3F(~2, ~0x35, ~0x0e2)|MCOND(~FCONDLG),	"9,f,g", 0, v9 },
{ "fmovlgq",	F3F(2, 0x35, 0x083)|MCOND(FCONDLG), (1<<18)|F3F(~2, ~0x35, ~0x083)|MCOND(~FCONDLG),	"6,f,g", 0, v9 },
{ "fmovlgq",	F3F(2, 0x35, 0x0a3)|MCOND(FCONDLG), (1<<18)|F3F(~2, ~0x35, ~0x0a3)|MCOND(~FCONDLG),	"7,f,g", 0, v9 },
{ "fmovlgq",	F3F(2, 0x35, 0x0c3)|MCOND(FCONDLG), (1<<18)|F3F(~2, ~0x35, ~0x0c3)|MCOND(~FCONDLG),	"8,f,g", 0, v9 },
{ "fmovlgq",	F3F(2, 0x35, 0x0e3)|MCOND(FCONDLG), (1<<18)|F3F(~2, ~0x35, ~0x0e3)|MCOND(~FCONDLG),	"9,f,g", 0, v9 },
{ "fmovlgs",	F3F(2, 0x35, 0x081)|MCOND(FCONDLG), (1<<18)|F3F(~2, ~0x35, ~0x081)|MCOND(~FCONDLG),	"6,f,g", 0, v9 },
{ "fmovlgs",	F3F(2, 0x35, 0x0a1)|MCOND(FCONDLG), (1<<18)|F3F(~2, ~0x35, ~0x0a1)|MCOND(~FCONDLG),	"7,f,g", 0, v9 },
{ "fmovlgs",	F3F(2, 0x35, 0x0c1)|MCOND(FCONDLG), (1<<18)|F3F(~2, ~0x35, ~0x0c1)|MCOND(~FCONDLG),	"8,f,g", 0, v9 },
{ "fmovlgs",	F3F(2, 0x35, 0x0e1)|MCOND(FCONDLG), (1<<18)|F3F(~2, ~0x35, ~0x0e1)|MCOND(~FCONDLG),	"9,f,g", 0, v9 },
{ "fmovlq",	F3F(2, 0x35, 0x083)|(1<<18)|MCOND(CONDL),  F3F(~2, ~0x35, ~0x083)|MCOND(~CONDL),	"z,f,g", 0, v9 },
{ "fmovlq",	F3F(2, 0x35, 0x083)|MCOND(FCONDL), (1<<18)|F3F(~2, ~0x35, ~0x083)|MCOND(~FCONDL),	"6,f,g", 0, v9 },
{ "fmovlq",	F3F(2, 0x35, 0x0a3)|(1<<18)|MCOND(CONDL),  F3F(~2, ~0x35, ~0x0a3)|MCOND(~CONDL),	"Z,f,g", 0, v9 },
{ "fmovlq",	F3F(2, 0x35, 0x0a3)|MCOND(FCONDL), (1<<18)|F3F(~2, ~0x35, ~0x0a3)|MCOND(~FCONDL),	"7,f,g", 0, v9 },
{ "fmovlq",	F3F(2, 0x35, 0x0c3)|MCOND(FCONDL), (1<<18)|F3F(~2, ~0x35, ~0x0c3)|MCOND(~FCONDL),	"8,f,g", 0, v9 },
{ "fmovlq",	F3F(2, 0x35, 0x0e3)|MCOND(FCONDL), (1<<18)|F3F(~2, ~0x35, ~0x0e3)|MCOND(~FCONDL),	"9,f,g", 0, v9 },
{ "fmovls",	F3F(2, 0x35, 0x081)|(1<<18)|MCOND(CONDL),  F3F(~2, ~0x35, ~0x081)|MCOND(~CONDL),	"z,f,g", 0, v9 },
{ "fmovls",	F3F(2, 0x35, 0x081)|MCOND(FCONDL), (1<<18)|F3F(~2, ~0x35, ~0x081)|MCOND(~FCONDL),	"6,f,g", 0, v9 },
{ "fmovls",	F3F(2, 0x35, 0x0a1)|(1<<18)|MCOND(CONDL),  F3F(~2, ~0x35, ~0x0a1)|MCOND(~CONDL),	"Z,f,g", 0, v9 },
{ "fmovls",	F3F(2, 0x35, 0x0a1)|MCOND(FCONDL), (1<<18)|F3F(~2, ~0x35, ~0x0a1)|MCOND(~FCONDL),	"7,f,g", 0, v9 },
{ "fmovls",	F3F(2, 0x35, 0x0c1)|MCOND(FCONDL), (1<<18)|F3F(~2, ~0x35, ~0x0c1)|MCOND(~FCONDL),	"8,f,g", 0, v9 },
{ "fmovls",	F3F(2, 0x35, 0x0e1)|MCOND(FCONDL), (1<<18)|F3F(~2, ~0x35, ~0x0e1)|MCOND(~FCONDL),	"9,f,g", 0, v9 },
{ "fmovlud",	F3F(2, 0x35, 0x082)|(1<<18)|MCOND(CONDLU), F3F(~2, ~0x35, ~0x082)|MCOND(~CONDLU),	"z,f,g", F_ALIAS, v9 },
{ "fmovlud",	F3F(2, 0x35, 0x0a2)|(1<<18)|MCOND(CONDLU), F3F(~2, ~0x35, ~0x0a2)|MCOND(~CONDLU),	"Z,f,g", F_ALIAS, v9 },
{ "fmovluq",	F3F(2, 0x35, 0x083)|(1<<18)|MCOND(CONDLU), F3F(~2, ~0x35, ~0x083)|MCOND(~CONDLU),	"z,f,g", F_ALIAS, v9 },
{ "fmovluq",	F3F(2, 0x35, 0x0a3)|(1<<18)|MCOND(CONDLU), F3F(~2, ~0x35, ~0x0a3)|MCOND(~CONDLU),	"Z,f,g", F_ALIAS, v9 },
{ "fmovlus",	F3F(2, 0x35, 0x081)|(1<<18)|MCOND(CONDLU), F3F(~2, ~0x35, ~0x081)|MCOND(~CONDLU),	"z,f,g", F_ALIAS, v9 },
{ "fmovlus",	F3F(2, 0x35, 0x0a1)|(1<<18)|MCOND(CONDLU), F3F(~2, ~0x35, ~0x0a1)|MCOND(~CONDLU),	"Z,f,g", F_ALIAS, v9 },
{ "fmovnd",	F3F(2, 0x35, 0x082)|(1<<18)|MCOND(CONDN),  F3F(~2, ~0x35, ~0x082)|MCOND(~CONDN),	"z,f,g", 0, v9 },
{ "fmovnd",	F3F(2, 0x35, 0x082)|MCOND(FCONDN), (1<<18)|F3F(~2, ~0x35, ~0x082)|MCOND(~FCONDN),	"6,f,g", 0, v9 },
{ "fmovnd",	F3F(2, 0x35, 0x0a2)|(1<<18)|MCOND(CONDN),  F3F(~2, ~0x35, ~0x0a2)|MCOND(~CONDN),	"Z,f,g", 0, v9 },
{ "fmovnd",	F3F(2, 0x35, 0x0a2)|MCOND(FCONDN), (1<<18)|F3F(~2, ~0x35, ~0x0a2)|MCOND(~FCONDN),	"7,f,g", 0, v9 },
{ "fmovnd",	F3F(2, 0x35, 0x0c2)|MCOND(FCONDN), (1<<18)|F3F(~2, ~0x35, ~0x0c2)|MCOND(~FCONDN),	"8,f,g", 0, v9 },
{ "fmovnd",	F3F(2, 0x35, 0x0e2)|MCOND(FCONDN), (1<<18)|F3F(~2, ~0x35, ~0x0e2)|MCOND(~FCONDN),	"9,f,g", 0, v9 },
{ "fmovned",	F3F(2, 0x35, 0x082)|(1<<18)|MCOND(CONDNE), F3F(~2, ~0x35, ~0x082)|MCOND(~CONDNE),	"z,f,g", 0, v9 },
{ "fmovned",	F3F(2, 0x35, 0x082)|MCOND(FCONDNE), (1<<18)|F3F(~2, ~0x35, ~0x082)|MCOND(~FCONDNE),	"6,f,g", 0, v9 },
{ "fmovned",	F3F(2, 0x35, 0x0a2)|(1<<18)|MCOND(CONDNE), F3F(~2, ~0x35, ~0x0a2)|MCOND(~CONDNE),	"Z,f,g", 0, v9 },
{ "fmovned",	F3F(2, 0x35, 0x0a2)|MCOND(FCONDNE), (1<<18)|F3F(~2, ~0x35, ~0x0a2)|MCOND(~FCONDNE),	"7,f,g", 0, v9 },
{ "fmovned",	F3F(2, 0x35, 0x0c2)|MCOND(FCONDNE), (1<<18)|F3F(~2, ~0x35, ~0x0c2)|MCOND(~FCONDNE),	"8,f,g", 0, v9 },
{ "fmovned",	F3F(2, 0x35, 0x0e2)|MCOND(FCONDNE), (1<<18)|F3F(~2, ~0x35, ~0x0e2)|MCOND(~FCONDNE),	"9,f,g", 0, v9 },
{ "fmovnegd",	F3F(2, 0x35, 0x082)|(1<<18)|MCOND(CONDNEG), F3F(~2, ~0x35, ~0x082)|MCOND(~CONDNEG),	"z,f,g", 0, v9 },
{ "fmovnegd",	F3F(2, 0x35, 0x0a2)|(1<<18)|MCOND(CONDNEG), F3F(~2, ~0x35, ~0x0a2)|MCOND(~CONDNEG),	"Z,f,g", 0, v9 },
{ "fmovnegq",	F3F(2, 0x35, 0x083)|(1<<18)|MCOND(CONDNEG), F3F(~2, ~0x35, ~0x083)|MCOND(~CONDNEG),	"z,f,g", 0, v9 },
{ "fmovnegq",	F3F(2, 0x35, 0x0a3)|(1<<18)|MCOND(CONDNEG), F3F(~2, ~0x35, ~0x0a3)|MCOND(~CONDNEG),	"Z,f,g", 0, v9 },
{ "fmovnegs",	F3F(2, 0x35, 0x081)|(1<<18)|MCOND(CONDNEG), F3F(~2, ~0x35, ~0x081)|MCOND(~CONDNEG),	"z,f,g", 0, v9 },
{ "fmovnegs",	F3F(2, 0x35, 0x0a1)|(1<<18)|MCOND(CONDNEG), F3F(~2, ~0x35, ~0x0a1)|MCOND(~CONDNEG),	"Z,f,g", 0, v9 },
{ "fmovneq",	F3F(2, 0x35, 0x083)|(1<<18)|MCOND(CONDNE),  F3F(~2, ~0x35, ~0x083)|MCOND(~CONDNE),	"z,f,g", 0, v9 },
{ "fmovneq",	F3F(2, 0x35, 0x083)|MCOND(FCONDNE), (1<<18)|F3F(~2, ~0x35, ~0x083)|MCOND(~FCONDNE),	"6,f,g", 0, v9 },
{ "fmovneq",	F3F(2, 0x35, 0x0a3)|(1<<18)|MCOND(CONDNE),  F3F(~2, ~0x35, ~0x0a3)|MCOND(~CONDNE),	"Z,f,g", 0, v9 },
{ "fmovneq",	F3F(2, 0x35, 0x0a3)|MCOND(FCONDNE), (1<<18)|F3F(~2, ~0x35, ~0x0a3)|MCOND(~FCONDNE),	"7,f,g", 0, v9 },
{ "fmovneq",	F3F(2, 0x35, 0x0c3)|MCOND(FCONDNE), (1<<18)|F3F(~2, ~0x35, ~0x0c3)|MCOND(~FCONDNE),	"8,f,g", 0, v9 },
{ "fmovneq",	F3F(2, 0x35, 0x0e3)|MCOND(FCONDNE), (1<<18)|F3F(~2, ~0x35, ~0x0e3)|MCOND(~FCONDNE),	"9,f,g", 0, v9 },
{ "fmovnes",	F3F(2, 0x35, 0x081)|(1<<18)|MCOND(CONDNE),  F3F(~2, ~0x35, ~0x081)|MCOND(~CONDNE),	"z,f,g", 0, v9 },
{ "fmovnes",	F3F(2, 0x35, 0x081)|MCOND(FCONDNE), (1<<18)|F3F(~2, ~0x35, ~0x081)|MCOND(~FCONDNE),	"6,f,g", 0, v9 },
{ "fmovnes",	F3F(2, 0x35, 0x0a1)|(1<<18)|MCOND(CONDNE),  F3F(~2, ~0x35, ~0x0a1)|MCOND(~CONDNE),	"Z,f,g", 0, v9 },
{ "fmovnes",	F3F(2, 0x35, 0x0a1)|MCOND(FCONDNE), (1<<18)|F3F(~2, ~0x35, ~0x0a1)|MCOND(~FCONDNE),	"7,f,g", 0, v9 },
{ "fmovnes",	F3F(2, 0x35, 0x0c1)|MCOND(FCONDNE), (1<<18)|F3F(~2, ~0x35, ~0x0c1)|MCOND(~FCONDNE),	"8,f,g", 0, v9 },
{ "fmovnes",	F3F(2, 0x35, 0x0e1)|MCOND(FCONDNE), (1<<18)|F3F(~2, ~0x35, ~0x0e1)|MCOND(~FCONDNE),	"9,f,g", 0, v9 },
{ "fmovnq",	F3F(2, 0x35, 0x083)|(1<<18)|MCOND(CONDN),  F3F(~2, ~0x35, ~0x083)|MCOND(~CONDN),	"z,f,g", 0, v9 },
{ "fmovnq",	F3F(2, 0x35, 0x083)|MCOND(FCONDN), (1<<18)|F3F(~2, ~0x35, ~0x083)|MCOND(~FCONDN),	"6,f,g", 0, v9 },
{ "fmovnq",	F3F(2, 0x35, 0x0a3)|(1<<18)|MCOND(CONDN),  F3F(~2, ~0x35, ~0x0a3)|MCOND(~CONDN),	"Z,f,g", 0, v9 },
{ "fmovnq",	F3F(2, 0x35, 0x0a3)|MCOND(FCONDN), (1<<18)|F3F(~2, ~0x35, ~0x0a3)|MCOND(~FCONDN),	"7,f,g", 0, v9 },
{ "fmovnq",	F3F(2, 0x35, 0x0c3)|MCOND(FCONDN), (1<<18)|F3F(~2, ~0x35, ~0x0c3)|MCOND(~FCONDN),	"8,f,g", 0, v9 },
{ "fmovnq",	F3F(2, 0x35, 0x0e3)|MCOND(FCONDN), (1<<18)|F3F(~2, ~0x35, ~0x0e3)|MCOND(~FCONDN),	"9,f,g", 0, v9 },
{ "fmovns",	F3F(2, 0x35, 0x081)|(1<<18)|MCOND(CONDN),  F3F(~2, ~0x35, ~0x081)|MCOND(~CONDN),	"z,f,g", 0, v9 },
{ "fmovns",	F3F(2, 0x35, 0x081)|MCOND(FCONDN), (1<<18)|F3F(~2, ~0x35, ~0x081)|MCOND(~FCONDN),	"6,f,g", 0, v9 },
{ "fmovns",	F3F(2, 0x35, 0x0a1)|(1<<18)|MCOND(CONDN),  F3F(~2, ~0x35, ~0x0a1)|MCOND(~CONDN),	"Z,f,g", 0, v9 },
{ "fmovns",	F3F(2, 0x35, 0x0a1)|MCOND(FCONDN), (1<<18)|F3F(~2, ~0x35, ~0x0a1)|MCOND(~FCONDN),	"7,f,g", 0, v9 },
{ "fmovns",	F3F(2, 0x35, 0x0c1)|MCOND(FCONDN), (1<<18)|F3F(~2, ~0x35, ~0x0c1)|MCOND(~FCONDN),	"8,f,g", 0, v9 },
{ "fmovns",	F3F(2, 0x35, 0x0e1)|MCOND(FCONDN), (1<<18)|F3F(~2, ~0x35, ~0x0e1)|MCOND(~FCONDN),	"9,f,g", 0, v9 },
{ "fmovnzd",	F3F(2, 0x35, 0x082)|(1<<18)|MCOND(CONDNZ), F3F(~2, ~0x35, ~0x082)|MCOND(~CONDNZ),	"z,f,g", F_ALIAS, v9 },
{ "fmovnzd",	F3F(2, 0x35, 0x082)|MCOND(FCONDNZ), (1<<18)|F3F(~2, ~0x35, ~0x082)|MCOND(~FCONDNZ),	"6,f,g", F_ALIAS, v9 },
{ "fmovnzd",	F3F(2, 0x35, 0x0a2)|(1<<18)|MCOND(CONDNZ), F3F(~2, ~0x35, ~0x0a2)|MCOND(~CONDNZ),	"Z,f,g", F_ALIAS, v9 },
{ "fmovnzd",	F3F(2, 0x35, 0x0a2)|MCOND(FCONDNZ), (1<<18)|F3F(~2, ~0x35, ~0x0a2)|MCOND(~FCONDNZ),	"7,f,g", F_ALIAS, v9 },
{ "fmovnzd",	F3F(2, 0x35, 0x0c2)|MCOND(FCONDNZ), (1<<18)|F3F(~2, ~0x35, ~0x0c2)|MCOND(~FCONDNZ),	"8,f,g", F_ALIAS, v9 },
{ "fmovnzd",	F3F(2, 0x35, 0x0e2)|MCOND(FCONDNZ), (1<<18)|F3F(~2, ~0x35, ~0x0e2)|MCOND(~FCONDNZ),	"9,f,g", F_ALIAS, v9 },
{ "fmovnzq",	F3F(2, 0x35, 0x083)|(1<<18)|MCOND(CONDNZ), F3F(~2, ~0x35, ~0x083)|MCOND(~CONDNZ),	"z,f,g", F_ALIAS, v9 },
{ "fmovnzq",	F3F(2, 0x35, 0x083)|MCOND(FCONDNZ), (1<<18)|F3F(~2, ~0x35, ~0x083)|MCOND(~FCONDNZ),	"6,f,g", F_ALIAS, v9 },
{ "fmovnzq",	F3F(2, 0x35, 0x0a3)|(1<<18)|MCOND(CONDNZ), F3F(~2, ~0x35, ~0x0a3)|MCOND(~CONDNZ),	"Z,f,g", F_ALIAS, v9 },
{ "fmovnzq",	F3F(2, 0x35, 0x0a3)|MCOND(FCONDNZ), (1<<18)|F3F(~2, ~0x35, ~0x0a3)|MCOND(~FCONDNZ),	"7,f,g", F_ALIAS, v9 },
{ "fmovnzq",	F3F(2, 0x35, 0x0c3)|MCOND(FCONDNZ), (1<<18)|F3F(~2, ~0x35, ~0x0c3)|MCOND(~FCONDNZ),	"8,f,g", F_ALIAS, v9 },
{ "fmovnzq",	F3F(2, 0x35, 0x0e3)|MCOND(FCONDNZ), (1<<18)|F3F(~2, ~0x35, ~0x0e3)|MCOND(~FCONDNZ),	"9,f,g", F_ALIAS, v9 },
{ "fmovnzs",	F3F(2, 0x35, 0x081)|(1<<18)|MCOND(CONDNZ), F3F(~2, ~0x35, ~0x081)|MCOND(~CONDNZ),	"z,f,g", F_ALIAS, v9 },
{ "fmovnzs",	F3F(2, 0x35, 0x081)|MCOND(FCONDNZ), (1<<18)|F3F(~2, ~0x35, ~0x081)|MCOND(~FCONDNZ),	"6,f,g", F_ALIAS, v9 },
{ "fmovnzs",	F3F(2, 0x35, 0x0a1)|(1<<18)|MCOND(CONDNZ), F3F(~2, ~0x35, ~0x0a1)|MCOND(~CONDNZ),	"Z,f,g", F_ALIAS, v9 },
{ "fmovnzs",	F3F(2, 0x35, 0x0a1)|MCOND(FCONDNZ), (1<<18)|F3F(~2, ~0x35, ~0x0a1)|MCOND(~FCONDNZ),	"7,f,g", F_ALIAS, v9 },
{ "fmovnzs",	F3F(2, 0x35, 0x0c1)|MCOND(FCONDNZ), (1<<18)|F3F(~2, ~0x35, ~0x0c1)|MCOND(~FCONDNZ),	"8,f,g", F_ALIAS, v9 },
{ "fmovnzs",	F3F(2, 0x35, 0x0e1)|MCOND(FCONDNZ), (1<<18)|F3F(~2, ~0x35, ~0x0e1)|MCOND(~FCONDNZ),	"9,f,g", F_ALIAS, v9 },
{ "fmovod",	F3F(2, 0x35, 0x082)|MCOND(FCONDO), (1<<18)|F3F(~2, ~0x35, ~0x082)|MCOND(~FCONDO),	"6,f,g", 0, v9 },
{ "fmovod",	F3F(2, 0x35, 0x0a2)|MCOND(FCONDO), (1<<18)|F3F(~2, ~0x35, ~0x0a2)|MCOND(~FCONDO),	"7,f,g", 0, v9 },
{ "fmovod",	F3F(2, 0x35, 0x0c2)|MCOND(FCONDO), (1<<18)|F3F(~2, ~0x35, ~0x0c2)|MCOND(~FCONDO),	"8,f,g", 0, v9 },
{ "fmovod",	F3F(2, 0x35, 0x0e2)|MCOND(FCONDO), (1<<18)|F3F(~2, ~0x35, ~0x0e2)|MCOND(~FCONDO),	"9,f,g", 0, v9 },
{ "fmovoq",	F3F(2, 0x35, 0x083)|MCOND(FCONDO), (1<<18)|F3F(~2, ~0x35, ~0x083)|MCOND(~FCONDO),	"6,f,g", 0, v9 },
{ "fmovoq",	F3F(2, 0x35, 0x0a3)|MCOND(FCONDO), (1<<18)|F3F(~2, ~0x35, ~0x0a3)|MCOND(~FCONDO),	"7,f,g", 0, v9 },
{ "fmovoq",	F3F(2, 0x35, 0x0c3)|MCOND(FCONDO), (1<<18)|F3F(~2, ~0x35, ~0x0c3)|MCOND(~FCONDO),	"8,f,g", 0, v9 },
{ "fmovoq",	F3F(2, 0x35, 0x0e3)|MCOND(FCONDO), (1<<18)|F3F(~2, ~0x35, ~0x0e3)|MCOND(~FCONDO),	"9,f,g", 0, v9 },
{ "fmovos",	F3F(2, 0x35, 0x081)|MCOND(FCONDO), (1<<18)|F3F(~2, ~0x35, ~0x081)|MCOND(~FCONDO),	"6,f,g", 0, v9 },
{ "fmovos",	F3F(2, 0x35, 0x0a1)|MCOND(FCONDO), (1<<18)|F3F(~2, ~0x35, ~0x0a1)|MCOND(~FCONDO),	"7,f,g", 0, v9 },
{ "fmovos",	F3F(2, 0x35, 0x0c1)|MCOND(FCONDO), (1<<18)|F3F(~2, ~0x35, ~0x0c1)|MCOND(~FCONDO),	"8,f,g", 0, v9 },
{ "fmovos",	F3F(2, 0x35, 0x0e1)|MCOND(FCONDO), (1<<18)|F3F(~2, ~0x35, ~0x0e1)|MCOND(~FCONDO),	"9,f,g", 0, v9 },
{ "fmovposd",	F3F(2, 0x35, 0x082)|(1<<18)|MCOND(CONDPOS), F3F(~2, ~0x35, ~0x082)|MCOND(~CONDPOS),	"z,f,g", 0, v9 },
{ "fmovposd",	F3F(2, 0x35, 0x0a2)|(1<<18)|MCOND(CONDPOS), F3F(~2, ~0x35, ~0x0a2)|MCOND(~CONDPOS),	"Z,f,g", 0, v9 },
{ "fmovposq",	F3F(2, 0x35, 0x083)|(1<<18)|MCOND(CONDPOS), F3F(~2, ~0x35, ~0x083)|MCOND(~CONDPOS),	"z,f,g", 0, v9 },
{ "fmovposq",	F3F(2, 0x35, 0x0a3)|(1<<18)|MCOND(CONDPOS), F3F(~2, ~0x35, ~0x0a3)|MCOND(~CONDPOS),	"Z,f,g", 0, v9 },
{ "fmovposs",	F3F(2, 0x35, 0x081)|(1<<18)|MCOND(CONDPOS), F3F(~2, ~0x35, ~0x081)|MCOND(~CONDPOS),	"z,f,g", 0, v9 },
{ "fmovposs",	F3F(2, 0x35, 0x0a1)|(1<<18)|MCOND(CONDPOS), F3F(~2, ~0x35, ~0x0a1)|MCOND(~CONDPOS),	"Z,f,g", 0, v9 },
{ "fmovud",	F3F(2, 0x35, 0x082)|MCOND(FCONDU), (1<<18)|F3F(~2, ~0x35, ~0x082)|MCOND(~FCONDU),	"6,f,g", 0, v9 },
{ "fmovud",	F3F(2, 0x35, 0x0a2)|MCOND(FCONDU), (1<<18)|F3F(~2, ~0x35, ~0x0a2)|MCOND(~FCONDU),	"7,f,g", 0, v9 },
{ "fmovud",	F3F(2, 0x35, 0x0c2)|MCOND(FCONDU), (1<<18)|F3F(~2, ~0x35, ~0x0c2)|MCOND(~FCONDU),	"8,f,g", 0, v9 },
{ "fmovud",	F3F(2, 0x35, 0x0e2)|MCOND(FCONDU), (1<<18)|F3F(~2, ~0x35, ~0x0e2)|MCOND(~FCONDU),	"9,f,g", 0, v9 },
{ "fmovued",	F3F(2, 0x35, 0x082)|MCOND(FCONDUE), (1<<18)|F3F(~2, ~0x35, ~0x082)|MCOND(~FCONDUE),	"6,f,g", 0, v9 },
{ "fmovued",	F3F(2, 0x35, 0x0a2)|MCOND(FCONDUE), (1<<18)|F3F(~2, ~0x35, ~0x0a2)|MCOND(~FCONDUE),	"7,f,g", 0, v9 },
{ "fmovued",	F3F(2, 0x35, 0x0c2)|MCOND(FCONDUE), (1<<18)|F3F(~2, ~0x35, ~0x0c2)|MCOND(~FCONDUE),	"8,f,g", 0, v9 },
{ "fmovued",	F3F(2, 0x35, 0x0e2)|MCOND(FCONDUE), (1<<18)|F3F(~2, ~0x35, ~0x0e2)|MCOND(~FCONDUE),	"9,f,g", 0, v9 },
{ "fmovueq",	F3F(2, 0x35, 0x083)|MCOND(FCONDUE), (1<<18)|F3F(~2, ~0x35, ~0x083)|MCOND(~FCONDUE),	"6,f,g", 0, v9 },
{ "fmovueq",	F3F(2, 0x35, 0x0a3)|MCOND(FCONDUE), (1<<18)|F3F(~2, ~0x35, ~0x0a3)|MCOND(~FCONDUE),	"7,f,g", 0, v9 },
{ "fmovueq",	F3F(2, 0x35, 0x0c3)|MCOND(FCONDUE), (1<<18)|F3F(~2, ~0x35, ~0x0c3)|MCOND(~FCONDUE),	"8,f,g", 0, v9 },
{ "fmovueq",	F3F(2, 0x35, 0x0e3)|MCOND(FCONDUE), (1<<18)|F3F(~2, ~0x35, ~0x0e3)|MCOND(~FCONDUE),	"9,f,g", 0, v9 },
{ "fmovues",	F3F(2, 0x35, 0x081)|MCOND(FCONDUE), (1<<18)|F3F(~2, ~0x35, ~0x081)|MCOND(~FCONDUE),	"6,f,g", 0, v9 },
{ "fmovues",	F3F(2, 0x35, 0x0a1)|MCOND(FCONDUE), (1<<18)|F3F(~2, ~0x35, ~0x0a1)|MCOND(~FCONDUE),	"7,f,g", 0, v9 },
{ "fmovues",	F3F(2, 0x35, 0x0c1)|MCOND(FCONDUE), (1<<18)|F3F(~2, ~0x35, ~0x0c1)|MCOND(~FCONDUE),	"8,f,g", 0, v9 },
{ "fmovues",	F3F(2, 0x35, 0x0e1)|MCOND(FCONDUE), (1<<18)|F3F(~2, ~0x35, ~0x0e1)|MCOND(~FCONDUE),	"9,f,g", 0, v9 },
{ "fmovugd",	F3F(2, 0x35, 0x082)|MCOND(FCONDUG), (1<<18)|F3F(~2, ~0x35, ~0x082)|MCOND(~FCONDUG),	"6,f,g", 0, v9 },
{ "fmovugd",	F3F(2, 0x35, 0x0a2)|MCOND(FCONDUG), (1<<18)|F3F(~2, ~0x35, ~0x0a2)|MCOND(~FCONDUG),	"7,f,g", 0, v9 },
{ "fmovugd",	F3F(2, 0x35, 0x0c2)|MCOND(FCONDUG), (1<<18)|F3F(~2, ~0x35, ~0x0c2)|MCOND(~FCONDUG),	"8,f,g", 0, v9 },
{ "fmovugd",	F3F(2, 0x35, 0x0e2)|MCOND(FCONDUG), (1<<18)|F3F(~2, ~0x35, ~0x0e2)|MCOND(~FCONDUG),	"9,f,g", 0, v9 },
{ "fmovuged",	F3F(2, 0x35, 0x082)|MCOND(FCONDUGE), (1<<18)|F3F(~2, ~0x35, ~0x082)|MCOND(~FCONDUGE),	"6,f,g", 0, v9 },
{ "fmovuged",	F3F(2, 0x35, 0x0a2)|MCOND(FCONDUGE), (1<<18)|F3F(~2, ~0x35, ~0x0a2)|MCOND(~FCONDUGE),	"7,f,g", 0, v9 },
{ "fmovuged",	F3F(2, 0x35, 0x0c2)|MCOND(FCONDUGE), (1<<18)|F3F(~2, ~0x35, ~0x0c2)|MCOND(~FCONDUGE),	"8,f,g", 0, v9 },
{ "fmovuged",	F3F(2, 0x35, 0x0e2)|MCOND(FCONDUGE), (1<<18)|F3F(~2, ~0x35, ~0x0e2)|MCOND(~FCONDUGE),	"9,f,g", 0, v9 },
{ "fmovugeq",	F3F(2, 0x35, 0x083)|MCOND(FCONDUGE), (1<<18)|F3F(~2, ~0x35, ~0x083)|MCOND(~FCONDUGE),	"6,f,g", 0, v9 },
{ "fmovugeq",	F3F(2, 0x35, 0x0a3)|MCOND(FCONDUGE), (1<<18)|F3F(~2, ~0x35, ~0x0a3)|MCOND(~FCONDUGE),	"7,f,g", 0, v9 },
{ "fmovugeq",	F3F(2, 0x35, 0x0c3)|MCOND(FCONDUGE), (1<<18)|F3F(~2, ~0x35, ~0x0c3)|MCOND(~FCONDUGE),	"8,f,g", 0, v9 },
{ "fmovugeq",	F3F(2, 0x35, 0x0e3)|MCOND(FCONDUGE), (1<<18)|F3F(~2, ~0x35, ~0x0e3)|MCOND(~FCONDUGE),	"9,f,g", 0, v9 },
{ "fmovuges",	F3F(2, 0x35, 0x081)|MCOND(FCONDUGE), (1<<18)|F3F(~2, ~0x35, ~0x081)|MCOND(~FCONDUGE),	"6,f,g", 0, v9 },
{ "fmovuges",	F3F(2, 0x35, 0x0a1)|MCOND(FCONDUGE), (1<<18)|F3F(~2, ~0x35, ~0x0a1)|MCOND(~FCONDUGE),	"7,f,g", 0, v9 },
{ "fmovuges",	F3F(2, 0x35, 0x0c1)|MCOND(FCONDUGE), (1<<18)|F3F(~2, ~0x35, ~0x0c1)|MCOND(~FCONDUGE),	"8,f,g", 0, v9 },
{ "fmovuges",	F3F(2, 0x35, 0x0e1)|MCOND(FCONDUGE), (1<<18)|F3F(~2, ~0x35, ~0x0e1)|MCOND(~FCONDUGE),	"9,f,g", 0, v9 },
{ "fmovugq",	F3F(2, 0x35, 0x083)|MCOND(FCONDUG), (1<<18)|F3F(~2, ~0x35, ~0x083)|MCOND(~FCONDUG),	"6,f,g", 0, v9 },
{ "fmovugq",	F3F(2, 0x35, 0x0a3)|MCOND(FCONDUG), (1<<18)|F3F(~2, ~0x35, ~0x0a3)|MCOND(~FCONDUG),	"7,f,g", 0, v9 },
{ "fmovugq",	F3F(2, 0x35, 0x0c3)|MCOND(FCONDUG), (1<<18)|F3F(~2, ~0x35, ~0x0c3)|MCOND(~FCONDUG),	"8,f,g", 0, v9 },
{ "fmovugq",	F3F(2, 0x35, 0x0e3)|MCOND(FCONDUG), (1<<18)|F3F(~2, ~0x35, ~0x0e3)|MCOND(~FCONDUG),	"9,f,g", 0, v9 },
{ "fmovugs",	F3F(2, 0x35, 0x081)|MCOND(FCONDUG), (1<<18)|F3F(~2, ~0x35, ~0x081)|MCOND(~FCONDUG),	"6,f,g", 0, v9 },
{ "fmovugs",	F3F(2, 0x35, 0x0a1)|MCOND(FCONDUG), (1<<18)|F3F(~2, ~0x35, ~0x0a1)|MCOND(~FCONDUG),	"7,f,g", 0, v9 },
{ "fmovugs",	F3F(2, 0x35, 0x0c1)|MCOND(FCONDUG), (1<<18)|F3F(~2, ~0x35, ~0x0c1)|MCOND(~FCONDUG),	"8,f,g", 0, v9 },
{ "fmovugs",	F3F(2, 0x35, 0x0e1)|MCOND(FCONDUG), (1<<18)|F3F(~2, ~0x35, ~0x0e1)|MCOND(~FCONDUG),	"9,f,g", 0, v9 },
{ "fmovuld",	F3F(2, 0x35, 0x082)|MCOND(FCONDUL), (1<<18)|F3F(~2, ~0x35, ~0x082)|MCOND(~FCONDUL),	"6,f,g", 0, v9 },
{ "fmovuld",	F3F(2, 0x35, 0x0a2)|MCOND(FCONDUL), (1<<18)|F3F(~2, ~0x35, ~0x0a2)|MCOND(~FCONDUL),	"7,f,g", 0, v9 },
{ "fmovuld",	F3F(2, 0x35, 0x0c2)|MCOND(FCONDUL), (1<<18)|F3F(~2, ~0x35, ~0x0c2)|MCOND(~FCONDUL),	"8,f,g", 0, v9 },
{ "fmovuld",	F3F(2, 0x35, 0x0e2)|MCOND(FCONDUL), (1<<18)|F3F(~2, ~0x35, ~0x0e2)|MCOND(~FCONDUL),	"9,f,g", 0, v9 },
{ "fmovuled",	F3F(2, 0x35, 0x082)|MCOND(FCONDULE), (1<<18)|F3F(~2, ~0x35, ~0x082)|MCOND(~FCONDULE),	"6,f,g", 0, v9 },
{ "fmovuled",	F3F(2, 0x35, 0x0a2)|MCOND(FCONDULE), (1<<18)|F3F(~2, ~0x35, ~0x0a2)|MCOND(~FCONDULE),	"7,f,g", 0, v9 },
{ "fmovuled",	F3F(2, 0x35, 0x0c2)|MCOND(FCONDULE), (1<<18)|F3F(~2, ~0x35, ~0x0c2)|MCOND(~FCONDULE),	"8,f,g", 0, v9 },
{ "fmovuled",	F3F(2, 0x35, 0x0e2)|MCOND(FCONDULE), (1<<18)|F3F(~2, ~0x35, ~0x0e2)|MCOND(~FCONDULE),	"9,f,g", 0, v9 },
{ "fmovuleq",	F3F(2, 0x35, 0x083)|MCOND(FCONDULE), (1<<18)|F3F(~2, ~0x35, ~0x083)|MCOND(~FCONDULE),	"6,f,g", 0, v9 },
{ "fmovuleq",	F3F(2, 0x35, 0x0a3)|MCOND(FCONDULE), (1<<18)|F3F(~2, ~0x35, ~0x0a3)|MCOND(~FCONDULE),	"7,f,g", 0, v9 },
{ "fmovuleq",	F3F(2, 0x35, 0x0c3)|MCOND(FCONDULE), (1<<18)|F3F(~2, ~0x35, ~0x0c3)|MCOND(~FCONDULE),	"8,f,g", 0, v9 },
{ "fmovuleq",	F3F(2, 0x35, 0x0e3)|MCOND(FCONDULE), (1<<18)|F3F(~2, ~0x35, ~0x0e3)|MCOND(~FCONDULE),	"9,f,g", 0, v9 },
{ "fmovules",	F3F(2, 0x35, 0x081)|MCOND(FCONDULE), (1<<18)|F3F(~2, ~0x35, ~0x081)|MCOND(~FCONDULE),	"6,f,g", 0, v9 },
{ "fmovules",	F3F(2, 0x35, 0x0a1)|MCOND(FCONDULE), (1<<18)|F3F(~2, ~0x35, ~0x0a1)|MCOND(~FCONDULE),	"7,f,g", 0, v9 },
{ "fmovules",	F3F(2, 0x35, 0x0c1)|MCOND(FCONDULE), (1<<18)|F3F(~2, ~0x35, ~0x0c1)|MCOND(~FCONDULE),	"8,f,g", 0, v9 },
{ "fmovules",	F3F(2, 0x35, 0x0e1)|MCOND(FCONDULE), (1<<18)|F3F(~2, ~0x35, ~0x0e1)|MCOND(~FCONDULE),	"9,f,g", 0, v9 },
{ "fmovulq",	F3F(2, 0x35, 0x083)|MCOND(FCONDUL), (1<<18)|F3F(~2, ~0x35, ~0x083)|MCOND(~FCONDUL),	"6,f,g", 0, v9 },
{ "fmovulq",	F3F(2, 0x35, 0x0a3)|MCOND(FCONDUL), (1<<18)|F3F(~2, ~0x35, ~0x0a3)|MCOND(~FCONDUL),	"7,f,g", 0, v9 },
{ "fmovulq",	F3F(2, 0x35, 0x0c3)|MCOND(FCONDUL), (1<<18)|F3F(~2, ~0x35, ~0x0c3)|MCOND(~FCONDUL),	"8,f,g", 0, v9 },
{ "fmovulq",	F3F(2, 0x35, 0x0e3)|MCOND(FCONDUL), (1<<18)|F3F(~2, ~0x35, ~0x0e3)|MCOND(~FCONDUL),	"9,f,g", 0, v9 },
{ "fmovuls",	F3F(2, 0x35, 0x081)|MCOND(FCONDUL), (1<<18)|F3F(~2, ~0x35, ~0x081)|MCOND(~FCONDUL),	"6,f,g", 0, v9 },
{ "fmovuls",	F3F(2, 0x35, 0x0a1)|MCOND(FCONDUL), (1<<18)|F3F(~2, ~0x35, ~0x0a1)|MCOND(~FCONDUL),	"7,f,g", 0, v9 },
{ "fmovuls",	F3F(2, 0x35, 0x0c1)|MCOND(FCONDUL), (1<<18)|F3F(~2, ~0x35, ~0x0c1)|MCOND(~FCONDUL),	"8,f,g", 0, v9 },
{ "fmovuls",	F3F(2, 0x35, 0x0e1)|MCOND(FCONDUL), (1<<18)|F3F(~2, ~0x35, ~0x0e1)|MCOND(~FCONDUL),	"9,f,g", 0, v9 },
{ "fmovuq",	F3F(2, 0x35, 0x083)|MCOND(FCONDU), (1<<18)|F3F(~2, ~0x35, ~0x083)|MCOND(~FCONDU),	"6,f,g", 0, v9 },
{ "fmovuq",	F3F(2, 0x35, 0x0a3)|MCOND(FCONDU), (1<<18)|F3F(~2, ~0x35, ~0x0a3)|MCOND(~FCONDU),	"7,f,g", 0, v9 },
{ "fmovuq",	F3F(2, 0x35, 0x0c3)|MCOND(FCONDU), (1<<18)|F3F(~2, ~0x35, ~0x0c3)|MCOND(~FCONDU),	"8,f,g", 0, v9 },
{ "fmovuq",	F3F(2, 0x35, 0x0e3)|MCOND(FCONDU), (1<<18)|F3F(~2, ~0x35, ~0x0e3)|MCOND(~FCONDU),	"9,f,g", 0, v9 },
{ "fmovus",	F3F(2, 0x35, 0x081)|MCOND(FCONDU), (1<<18)|F3F(~2, ~0x35, ~0x081)|MCOND(~FCONDU),	"6,f,g", 0, v9 },
{ "fmovus",	F3F(2, 0x35, 0x0a1)|MCOND(FCONDU), (1<<18)|F3F(~2, ~0x35, ~0x0a1)|MCOND(~FCONDU),	"7,f,g", 0, v9 },
{ "fmovus",	F3F(2, 0x35, 0x0c1)|MCOND(FCONDU), (1<<18)|F3F(~2, ~0x35, ~0x0c1)|MCOND(~FCONDU),	"8,f,g", 0, v9 },
{ "fmovus",	F3F(2, 0x35, 0x0e1)|MCOND(FCONDU), (1<<18)|F3F(~2, ~0x35, ~0x0e1)|MCOND(~FCONDU),	"9,f,g", 0, v9 },
{ "fmovvcd",	F3F(2, 0x35, 0x082)|(1<<18)|MCOND(CONDVC), F3F(~2, ~0x35, ~0x082)|MCOND(~CONDVC),	"z,f,g", 0, v9 },
{ "fmovvcd",	F3F(2, 0x35, 0x0a2)|(1<<18)|MCOND(CONDVC), F3F(~2, ~0x35, ~0x0a2)|MCOND(~CONDVC),	"Z,f,g", 0, v9 },
{ "fmovvcq",	F3F(2, 0x35, 0x083)|(1<<18)|MCOND(CONDVC), F3F(~2, ~0x35, ~0x083)|MCOND(~CONDVC),	"z,f,g", 0, v9 },
{ "fmovvcq",	F3F(2, 0x35, 0x0a3)|(1<<18)|MCOND(CONDVC), F3F(~2, ~0x35, ~0x0a3)|MCOND(~CONDVC),	"Z,f,g", 0, v9 },
{ "fmovvcs",	F3F(2, 0x35, 0x081)|(1<<18)|MCOND(CONDVC), F3F(~2, ~0x35, ~0x081)|MCOND(~CONDVC),	"z,f,g", 0, v9 },
{ "fmovvcs",	F3F(2, 0x35, 0x0a1)|(1<<18)|MCOND(CONDVC), F3F(~2, ~0x35, ~0x0a1)|MCOND(~CONDVC),	"Z,f,g", 0, v9 },
{ "fmovvsd",	F3F(2, 0x35, 0x082)|(1<<18)|MCOND(CONDVS), F3F(~2, ~0x35, ~0x082)|MCOND(~CONDVS),	"z,f,g", 0, v9 },
{ "fmovvsd",	F3F(2, 0x35, 0x0a2)|(1<<18)|MCOND(CONDVS), F3F(~2, ~0x35, ~0x0a2)|MCOND(~CONDVS),	"Z,f,g", 0, v9 },
{ "fmovvsq",	F3F(2, 0x35, 0x083)|(1<<18)|MCOND(CONDVS), F3F(~2, ~0x35, ~0x083)|MCOND(~CONDVS),	"z,f,g", 0, v9 },
{ "fmovvsq",	F3F(2, 0x35, 0x0a3)|(1<<18)|MCOND(CONDVS), F3F(~2, ~0x35, ~0x0a3)|MCOND(~CONDVS),	"Z,f,g", 0, v9 },
{ "fmovvss",	F3F(2, 0x35, 0x081)|(1<<18)|MCOND(CONDVS), F3F(~2, ~0x35, ~0x081)|MCOND(~CONDVS),	"z,f,g", 0, v9 },
{ "fmovvss",	F3F(2, 0x35, 0x0a1)|(1<<18)|MCOND(CONDVS), F3F(~2, ~0x35, ~0x0a1)|MCOND(~CONDVS),	"Z,f,g", 0, v9 },
{ "fmovzd",	F3F(2, 0x35, 0x082)|(1<<18)|MCOND(CONDZ),   F3F(~2, ~0x35, ~0x082)|MCOND(~CONDZ),	"z,f,g", F_ALIAS, v9 },
{ "fmovzd",	F3F(2, 0x35, 0x082)|MCOND(FCONDZ), (1<<18)|F3F(~2, ~0x35, ~0x082)|MCOND(~FCONDZ),	"6,f,g", F_ALIAS, v9 },
{ "fmovzd",	F3F(2, 0x35, 0x0a2)|(1<<18)|MCOND(CONDZ),   F3F(~2, ~0x35, ~0x0a2)|MCOND(~CONDZ),	"Z,f,g", F_ALIAS, v9 },
{ "fmovzd",	F3F(2, 0x35, 0x0a2)|MCOND(FCONDZ), (1<<18)|F3F(~2, ~0x35, ~0x0a2)|MCOND(~FCONDZ),	"7,f,g", F_ALIAS, v9 },
{ "fmovzd",	F3F(2, 0x35, 0x0c2)|MCOND(FCONDZ), (1<<18)|F3F(~2, ~0x35, ~0x0c2)|MCOND(~FCONDZ),	"8,f,g", F_ALIAS, v9 },
{ "fmovzd",	F3F(2, 0x35, 0x0e2)|MCOND(FCONDZ), (1<<18)|F3F(~2, ~0x35, ~0x0e2)|MCOND(~FCONDZ),	"9,f,g", F_ALIAS, v9 },
{ "fmovzq",	F3F(2, 0x35, 0x083)|(1<<18)|MCOND(CONDZ),   F3F(~2, ~0x35, ~0x083)|MCOND(~CONDZ),	"z,f,g", F_ALIAS, v9 },
{ "fmovzq",	F3F(2, 0x35, 0x083)|MCOND(FCONDZ), (1<<18)|F3F(~2, ~0x35, ~0x083)|MCOND(~FCONDZ),	"6,f,g", F_ALIAS, v9 },
{ "fmovzq",	F3F(2, 0x35, 0x0a3)|(1<<18)|MCOND(CONDZ),   F3F(~2, ~0x35, ~0x0a3)|MCOND(~CONDZ),	"Z,f,g", F_ALIAS, v9 },
{ "fmovzq",	F3F(2, 0x35, 0x0a3)|MCOND(FCONDZ), (1<<18)|F3F(~2, ~0x35, ~0x0a3)|MCOND(~FCONDZ),	"7,f,g", F_ALIAS, v9 },
{ "fmovzq",	F3F(2, 0x35, 0x0c3)|MCOND(FCONDZ), (1<<18)|F3F(~2, ~0x35, ~0x0c3)|MCOND(~FCONDZ),	"8,f,g", F_ALIAS, v9 },
{ "fmovzq",	F3F(2, 0x35, 0x0e3)|MCOND(FCONDZ), (1<<18)|F3F(~2, ~0x35, ~0x0e3)|MCOND(~FCONDZ),	"9,f,g", F_ALIAS, v9 },
{ "fmovzs",	F3F(2, 0x35, 0x081)|(1<<18)|MCOND(CONDZ),   F3F(~2, ~0x35, ~0x081)|MCOND(~CONDZ),	"z,f,g", F_ALIAS, v9 },
{ "fmovzs",	F3F(2, 0x35, 0x081)|MCOND(FCONDZ), (1<<18)|F3F(~2, ~0x35, ~0x081)|MCOND(~FCONDZ),	"6,f,g", F_ALIAS, v9 },
{ "fmovzs",	F3F(2, 0x35, 0x0a1)|(1<<18)|MCOND(CONDZ),   F3F(~2, ~0x35, ~0x0a1)|MCOND(~CONDZ),	"Z,f,g", F_ALIAS, v9 },
{ "fmovzs",	F3F(2, 0x35, 0x0a1)|MCOND(FCONDZ), (1<<18)|F3F(~2, ~0x35, ~0x0a1)|MCOND(~FCONDZ),	"7,f,g", F_ALIAS, v9 },
{ "fmovzs",	F3F(2, 0x35, 0x0c1)|MCOND(FCONDZ), (1<<18)|F3F(~2, ~0x35, ~0x0c1)|MCOND(~FCONDZ),	"8,f,g", F_ALIAS, v9 },
{ "fmovzs",	F3F(2, 0x35, 0x0e1)|MCOND(FCONDZ), (1<<18)|F3F(~2, ~0x35, ~0x0e1)|MCOND(~FCONDZ),	"9,f,g", F_ALIAS, v9 },

#define brfc(opcode, mask, lose) \
 { opcode, (mask), ANNUL|(lose), "l",   F_DELAYED, v6 }, \
 { opcode, (mask)|ANNUL, (lose), ",al", F_DELAYED, v6 }

#define brfcx(opcode, mask, lose) /* v9 */ \
 { opcode, FBFCC(0)|(mask), ANNUL|BPRED|FBFCC(~0)|(lose), "6,G",   F_DELAYED, v9 }, \
 { opcode, FBFCC(0)|(mask), ANNUL|BPRED|FBFCC(~0)|(lose), ",N6,G",   F_DELAYED, v9 }, \
 { opcode, FBFCC(0)|(mask)|ANNUL, BPRED|FBFCC(~0)|(lose), ",a,N6,G", F_DELAYED, v9 }, \
 { opcode, FBFCC(0)|(mask)|BPRED, ANNUL|FBFCC(~0)|(lose), ",T6,G",   F_DELAYED, v9 }, \
 { opcode, FBFCC(0)|(mask)|BPRED|ANNUL, FBFCC(~0)|(lose), ",a,T6,G", F_DELAYED, v9 }, \
 { opcode, FBFCC(1)|(mask), ANNUL|BPRED|FBFCC(~1)|(lose), "7,G",   F_DELAYED, v9 }, \
 { opcode, FBFCC(1)|(mask), ANNUL|BPRED|FBFCC(~1)|(lose), ",N7,G",   F_DELAYED, v9 }, \
 { opcode, FBFCC(1)|(mask)|ANNUL, BPRED|FBFCC(~1)|(lose), ",a,N7,G", F_DELAYED, v9 }, \
 { opcode, FBFCC(1)|(mask)|BPRED, ANNUL|FBFCC(~1)|(lose), ",T7,G",   F_DELAYED, v9 }, \
 { opcode, FBFCC(1)|(mask)|BPRED|ANNUL, FBFCC(~1)|(lose), ",a,T7,G", F_DELAYED, v9 }, \
 { opcode, FBFCC(2)|(mask), ANNUL|BPRED|FBFCC(~2)|(lose), "8,G",   F_DELAYED, v9 }, \
 { opcode, FBFCC(2)|(mask), ANNUL|BPRED|FBFCC(~2)|(lose), ",N8,G",   F_DELAYED, v9 }, \
 { opcode, FBFCC(2)|(mask)|ANNUL, BPRED|FBFCC(~2)|(lose), ",a,N8,G", F_DELAYED, v9 }, \
 { opcode, FBFCC(2)|(mask)|BPRED, ANNUL|FBFCC(~2)|(lose), ",T8,G",   F_DELAYED, v9 }, \
 { opcode, FBFCC(2)|(mask)|BPRED|ANNUL, FBFCC(~2)|(lose), ",a,T8,G", F_DELAYED, v9 }, \
 { opcode, FBFCC(3)|(mask), ANNUL|BPRED|FBFCC(~3)|(lose), "9,G",   F_DELAYED, v9 }, \
 { opcode, FBFCC(3)|(mask), ANNUL|BPRED|FBFCC(~3)|(lose), ",N9,G",   F_DELAYED, v9 }, \
 { opcode, FBFCC(3)|(mask)|ANNUL, BPRED|FBFCC(~3)|(lose), ",a,N9,G", F_DELAYED, v9 }, \
 { opcode, FBFCC(3)|(mask)|BPRED, ANNUL|FBFCC(~3)|(lose), ",T9,G",   F_DELAYED, v9 }, \
 { opcode, FBFCC(3)|(mask)|BPRED|ANNUL, FBFCC(~3)|(lose), ",a,T9,G", F_DELAYED, v9 }

#define condfc(fop, cop, mask) \
  brfc(fop, F2(0, 6)|COND(mask), F2(~0, ~6)|COND(~(mask))), \
  brfcx(fop, F2(0, 5)|COND(mask), F2(~0, ~5)|COND(~(mask))), /* v9 */ \
  brfc(cop, F2(0, 7)|COND(mask), F2(~0, ~7)|COND(~(mask))) \

condfc("fb",	"cb",	 0x8),
condfc("fba",	"cba",	 0x8),
condfc("fbe",	"cb0",	 0x9),
condfc("fbg",	"cb2",	 0x6),
condfc("fbge",	"cb02",	 0xb),
condfc("fbl",	"cb1",	 0x4),
condfc("fble",	"cb01",	 0xd),
condfc("fblg",	"cb12",	 0x2),
condfc("fbn",	"cbn",	 0x0),
condfc("fbne",	"cb123", 0x1),
condfc("fbo",	"cb012", 0xf),
condfc("fbu",	"cb3",	 0x7),
condfc("fbue",	"cb03",	 0xa),
condfc("fbug",	"cb23",	 0x5),
condfc("fbuge",	"cb023", 0xc),
condfc("fbul",	"cb13",	 0x3),
condfc("fbule",	"cb013", 0xe),

#undef condfc
#undef brfc

{ "jmp",	F3(2, 0x38, 0), F3(~2, ~0x38, ~0)|RD_G0|ASI(~0),	"1+2", F_DELAYED, v6 }, /* jmpl rs1+rs2,%g0 */
{ "jmp",	F3(2, 0x38, 0), F3(~2, ~0x38, ~0)|RD_G0|ASI_RS2(~0),	"1", F_DELAYED, v6 }, /* jmpl rs1+%g0,%g0 */
{ "jmp",	F3(2, 0x38, 1), F3(~2, ~0x38, ~1)|RD_G0,		"1+i", F_DELAYED, v6 }, /* jmpl rs1+i,%g0 */
{ "jmp",	F3(2, 0x38, 1), F3(~2, ~0x38, ~1)|RD_G0,		"i+1", F_DELAYED, v6 }, /* jmpl i+rs1,%g0 */
{ "jmp",	F3(2, 0x38, 1), F3(~2, ~0x38, ~1)|RD_G0|RS1_G0,	"i", F_DELAYED, v6 }, /* jmpl %g0+i,%g0 */

{ "nop",	F2(0, 4), F2(~0, ~4), "", 0, v6 }, /* sethi 0, %g0 */

{ "set",	F2(0x0, 0x4), F2(~0x0, ~0x4), "Sh,d", F_ALIAS, v6 },

{ "sethi",	F2(0x0, 0x4), F2(~0x0, ~0x4), "h,d", 0, v6 },

{ "taddcc",	F3(2, 0x20, 0), F3(~2, ~0x20, ~0)|ASI(~0),	"1,2,d", 0, v6 },
{ "taddcc",	F3(2, 0x20, 1), F3(~2, ~0x20, ~1),		"1,i,d", 0, v6 },
{ "taddcc",	F3(2, 0x20, 1), F3(~2, ~0x20, ~1),		"i,1,d", 0, v6 },
{ "taddcctv",	F3(2, 0x22, 0), F3(~2, ~0x22, ~0)|ASI(~0),	"1,2,d", 0, v6 },
{ "taddcctv",	F3(2, 0x22, 1), F3(~2, ~0x22, ~1),		"1,i,d", 0, v6 },
{ "taddcctv",	F3(2, 0x22, 1), F3(~2, ~0x22, ~1),		"i,1,d", 0, v6 },

{ "tsubcc",	F3(2, 0x21, 0), F3(~2, ~0x21, ~0)|ASI(~0),	"1,2,d", 0, v6 },
{ "tsubcc",	F3(2, 0x21, 1), F3(~2, ~0x21, ~1),		"1,i,d", 0, v6 },
{ "tsubcctv",	F3(2, 0x0b, 0), F3(~2, ~0x0b, ~0)|ASI(~0),	"1,2,d", 0, v6 },
{ "tsubcctv",	F3(2, 0x0b, 1), F3(~2, ~0x0b, ~1),		"1,i,d", 0, v6 },

{ "unimp",	F2(0x0, 0x0), 0xffffffff, "l", 0, v6 },

{ "iflush",	F3(2, 0x3b, 0), F3(~2, ~0x3b, ~0)|ASI(~0),	"1+2", 0, v6 },
{ "iflush",	F3(2, 0x3b, 1), F3(~2, ~0x3b, ~1),		"1+i", 0, v6 },
{ "iflush",	F3(2, 0x3b, 1), F3(~2, ~0x3b, ~1),		"i+1", 0, v6 },
{ "iflush",	F3(2, 0x3b, 1), F3(~2, ~0x3b, ~1)|RS1_G0,	"i", 0, v6 },

{ "xnor",	F3(2, 0x07, 0), F3(~2, ~0x07, ~0)|ASI(~0),	"1,2,d", 0, v6 },
{ "xnor",	F3(2, 0x07, 1), F3(~2, ~0x07, ~1),		"1,i,d", 0, v6 },
{ "xnor",	F3(2, 0x07, 1), F3(~2, ~0x07, ~1),		"i,1,d", 0, v6 },
{ "xnorcc",	F3(2, 0x17, 0), F3(~2, ~0x17, ~0)|ASI(~0),	"1,2,d", 0, v6 },
{ "xnorcc",	F3(2, 0x17, 1), F3(~2, ~0x17, ~1),		"1,i,d", 0, v6 },
{ "xnorcc",	F3(2, 0x17, 1), F3(~2, ~0x17, ~1),		"i,1,d", 0, v6 },
{ "xor",	F3(2, 0x03, 0), F3(~2, ~0x03, ~0)|ASI(~0),	"1,2,d", 0, v6 },
{ "xor",	F3(2, 0x03, 1), F3(~2, ~0x03, ~1),		"1,i,d", 0, v6 },
{ "xor",	F3(2, 0x03, 1), F3(~2, ~0x03, ~1),		"i,1,d", 0, v6 },
{ "xorcc",	F3(2, 0x13, 0), F3(~2, ~0x13, ~0)|ASI(~0),	"1,2,d", 0, v6 },
{ "xorcc",	F3(2, 0x13, 1), F3(~2, ~0x13, ~1),		"1,i,d", 0, v6 },
{ "xorcc",	F3(2, 0x13, 1), F3(~2, ~0x13, ~1),		"i,1,d", 0, v6 },

{ "not",	F3(2, 0x07, 0), F3(~2, ~0x07, ~0)|ASI(~0), "1,d", F_ALIAS, v6 }, /* xnor rs1,%0,rd */
{ "not",	F3(2, 0x07, 0), F3(~2, ~0x07, ~0)|ASI(~0), "r", F_ALIAS, v6 }, /* xnor rd,%0,rd */

{ "btog",	F3(2, 0x03, 0), F3(~2, ~0x03, ~0)|ASI(~0),	"2,r", F_ALIAS, v6 }, /* xor rd,rs2,rd */
{ "btog",	F3(2, 0x03, 1), F3(~2, ~0x03, ~1),		"i,r", F_ALIAS, v6 }, /* xor rd,i,rd */

{ "fpop1",	F3F(2, 0x34, 0), F3F(~2, ~0x34, ~1), "[1+2],d", 0, v6 },
{ "fpop2",	F3F(2, 0x35, 0), F3F(~2, ~0x35, ~1), "[1+2],d", 0, v6 },

/* float-start */
{ "fdtoi",	F3F(2, 0x34, 0x0d2), F3F(~2, ~0x34, ~0x0d2)|RS1_G0, "f,g", 0, v6 },
{ "fstoi",	F3F(2, 0x34, 0x0d1), F3F(~2, ~0x34, ~0x0d1)|RS1_G0, "f,g", 0, v6 },

 /* all of these conversions are confused and probably wrong. */
{ "fitod",	F3F(2, 0x34, 0x0c8), F3F(~2, ~0x34, ~0x0c8)|RS1_G0, "f,g", 0, v6 },
{ "fitos",	F3F(2, 0x34, 0x0c4), F3F(~2, ~0x34, ~0x0c4)|RS1_G0, "f,g", 0, v6 },

{ "fitox",	F3F(2, 0x34, 0x0cc), F3F(~2, ~0x34, ~0x0cc)|RS1_G0, "f,g", 0, v6 }, /* collides in mneumonic with cypress */
 /* fitox collides in opf between cypress and v8, mneumonic between v6 and cypress */
{ "fitox",	F3F(2, 0x34, 0x0cc), F3F(~2, ~0x34, ~0x0cc)|RS1_G0, "f,g", 0, cypress }, /* collides */
{ "fitoq",	F3F(2, 0x34, 0x0cc), F3F(~2, ~0x34, ~0x0cc)|RS1_G0, "f,g", 0, v8 }, /* collides in opf with cypress */

{ "fxtoq",	F3F(2, 0x34, 0x08c), F3F(~2, ~0x34, ~0x08c)|RS1_G0, "f,g", 0, v9 },

{ "fdtoq",	F3F(2, 0x34, 0x0ce), F3F(~2, ~0x34, ~0x0ce)|RS1_G0, "f,g", 0, v8 },
{ "fdtos",	F3F(2, 0x34, 0x0c6), F3F(~2, ~0x34, ~0x0c6)|RS1_G0, "f,g", 0, v6 },
{ "fqtod",	F3F(2, 0x34, 0x0cb), F3F(~2, ~0x34, ~0x0cb)|RS1_G0, "f,g", 0, v8 },
{ "fqtos",	F3F(2, 0x34, 0x0c7), F3F(~2, ~0x34, ~0x0c7)|RS1_G0, "f,g", 0, v8 },
{ "fstod",	F3F(2, 0x34, 0x0c9), F3F(~2, ~0x34, ~0x0c9)|RS1_G0, "f,g", 0, v6 },
{ "fstoq",	F3F(2, 0x34, 0x0cd), F3F(~2, ~0x34, ~0x0cd)|RS1_G0, "f,g", 0, v8 },

{ "fqtox",	F3F(2, 0x34, 0x083), F3F(~2, ~0x34, ~0x083)|RS1_G0, "f,g", 0, v9 },

{ "fxtos",	F3F(2, 0x34, 0x0c7), F3F(~2, ~0x34, ~0x0c7)|RS1_G0, "f,g", 0, v7 }, /* these collide on the mneumonic */
{ "fxtos",	F3F(2, 0x34, 0x084), F3F(~2, ~0x34, ~0x084)|RS1_G0, "f,g", 0, v9 },
{ "fxtos",	F3F(2, 0x34, 0x0c7), F3F(~2, ~0x34, ~0x0c7)|RS1_G0, "f,g", 0, cypress },

{ "fdtox",	F3F(2, 0x34, 0x0ce), F3F(~2, ~0x34, ~0x0ce)|RS1_G0, "f,g", 0, cypress }, /* mneumonic collisions */
{ "fdtox",	F3F(2, 0x34, 0x082), F3F(~2, ~0x34, ~0x082)|RS1_G0, "f,g", 0, v9 },

{ "fstox",	F3F(2, 0x34, 0x0cd), F3F(~2, ~0x34, ~0x0cd)|RS1_G0, "f,g", 0, cypress },
{ "fstox",	F3F(2, 0x34, 0x081), F3F(~2, ~0x34, ~0x081)|RS1_G0, "f,g", 0, v9 },

{ "fqtoi",	F3F(2, 0x34, 0x0d3), F3F(~2, ~0x34, ~0x0d3)|RS1_G0, "f,g", 0, v8 },
{ "fxtoi",	F3F(2, 0x34, 0x0d3), F3F(~2, ~0x34, ~0x0d3)|RS1_G0, "f,g", 0, cypress },

{ "fxtod",	F3F(2, 0x34, 0x0cb), F3F(~2, ~0x34, ~0x0cb)|RS1_G0, "f,g", 0, cypress }, /* collide in opf & mneumonic */
{ "fxtod",	F3F(2, 0x34, 0x088), F3F(~2, ~0x34, ~0x088)|RS1_G0, "f,g", 0, v9 },

{ "fdivd",	F3F(2, 0x34, 0x04e), F3F(~2, ~0x34, ~0x04e), "e,f,g", 0, v6 },
{ "fdivq",	F3F(2, 0x34, 0x04f), F3F(~2, ~0x34, ~0x04f), "e,f,g", 0, v8 },
{ "fdivs",	F3F(2, 0x34, 0x04d), F3F(~2, ~0x34, ~0x04d), "e,f,g", 0, v6 },
{ "fdivx",	F3F(2, 0x34, 0x04f), F3F(~2, ~0x34, ~0x04f), "e,f,g", 0, cypress },
{ "fmuld",	F3F(2, 0x34, 0x04a), F3F(~2, ~0x34, ~0x04a), "e,f,g", 0, v6 },
{ "fmulq",	F3F(2, 0x34, 0x04b), F3F(~2, ~0x34, ~0x04b), "e,f,g", 0, v8 },
{ "fmuls",	F3F(2, 0x34, 0x049), F3F(~2, ~0x34, ~0x049), "e,f,g", 0, v6 },
{ "fmulx",	F3F(2, 0x34, 0x04b), F3F(~2, ~0x34, ~0x04b), "e,f,g", 0, cypress },

{ "fdmulq",	F3F(2, 0x34, 0x06e), F3F(~2, ~0x34, ~0x06e), "e,f,g", 0, v8 },
{ "fsmuld",	F3F(2, 0x34, 0x069), F3F(~2, ~0x34, ~0x069), "e,f,g", 0, v8 },

{ "fsqrtd",	F3F(2, 0x34, 0x02a), F3F(~2, ~0x34, ~0x02a)|RS1_G0, "f,g", 0, v7 },
{ "fsqrtq",	F3F(2, 0x34, 0x02b), F3F(~2, ~0x34, ~0x02b)|RS1_G0, "f,g", 0, v8 },
{ "fsqrts",	F3F(2, 0x34, 0x029), F3F(~2, ~0x34, ~0x029)|RS1_G0, "f,g", 0, v7 },
{ "fsqrtx",	F3F(2, 0x34, 0x02b), F3F(~2, ~0x34, ~0x02b)|RS1_G0, "f,g", 0, cypress },

{ "fabsd",	F3F(2, 0x34, 0x00a), F3F(~2, ~0x34, ~0x00a)|RS1_G0, "f,g", 0, v9 },
{ "fabsq",	F3F(2, 0x34, 0x00b), F3F(~2, ~0x34, ~0x00b)|RS1_G0, "f,g", 0, v6 },
{ "fabss",	F3F(2, 0x34, 0x009), F3F(~2, ~0x34, ~0x009)|RS1_G0, "f,g", 0, v6 },
{ "fmovd",	F3F(2, 0x34, 0x002), F3F(~2, ~0x34, ~0x002)|RS1_G0, "f,g", 0, v9 },
{ "fmovq",	F3F(2, 0x34, 0x003), F3F(~2, ~0x34, ~0x003)|RS1_G0, "f,g", 0, v6 },
{ "fmovs",	F3F(2, 0x34, 0x001), F3F(~2, ~0x34, ~0x001)|RS1_G0, "f,g", 0, v6 },
{ "fnegd",	F3F(2, 0x34, 0x006), F3F(~2, ~0x34, ~0x006)|RS1_G0, "f,g", 0, v9 },
{ "fnegq",	F3F(2, 0x34, 0x007), F3F(~2, ~0x34, ~0x007)|RS1_G0, "f,g", 0, v6 },
{ "fnegs",	F3F(2, 0x34, 0x005), F3F(~2, ~0x34, ~0x005)|RS1_G0, "f,g", 0, v6 },

{ "popc",	F3(2, 0x2d, 0), F3(~2, ~0x2d, ~0)|(0x3fff<<5),	"2,d", 0, v9 },

{ "faddd",	F3F(2, 0x34, 0x042), F3F(~2, ~0x34, ~0x042), "e,f,g", 0, v6 },
{ "faddq",	F3F(2, 0x34, 0x043), F3F(~2, ~0x34, ~0x043), "e,f,g", 0, v8 },
{ "fadds",	F3F(2, 0x34, 0x041), F3F(~2, ~0x34, ~0x041), "e,f,g", 0, v6 },
{ "faddx",	F3F(2, 0x34, 0x043), F3F(~2, ~0x34, ~0x043), "e,f,g", 0, cypress },
{ "fsubd",	F3F(2, 0x34, 0x046), F3F(~2, ~0x34, ~0x046), "e,f,g", 0, v6 },
{ "fsubq",	F3F(2, 0x34, 0x047), F3F(~2, ~0x34, ~0x047), "e,f,g", 0, v8 },
{ "fsubs",	F3F(2, 0x34, 0x045), F3F(~2, ~0x34, ~0x045), "e,f,g", 0, v6 },
{ "fsubx",	F3F(2, 0x34, 0x047), F3F(~2, ~0x34, ~0x047), "e,f,g", 0, cypress },

#define CMPFCC(x)	(((x)&0x3)<<25)

{ "fcmpd",	          F3F(2, 0x35, 0x052),            F3F(~2, ~0x35, ~0x052)|RS1_G0, "e,f",   0, v6 },
{ "fcmpd",	CMPFCC(0)|F3F(2, 0x35, 0x052), CMPFCC(~0)|F3F(~2, ~0x35, ~0x052),	 "6,e,f", 0, v9 },
{ "fcmpd",	CMPFCC(1)|F3F(2, 0x35, 0x052), CMPFCC(~1)|F3F(~2, ~0x35, ~0x052),	 "7,e,f", 0, v9 },
{ "fcmpd",	CMPFCC(2)|F3F(2, 0x35, 0x052), CMPFCC(~2)|F3F(~2, ~0x35, ~0x052),	 "8,e,f", 0, v9 },
{ "fcmpd",	CMPFCC(3)|F3F(2, 0x35, 0x052), CMPFCC(~3)|F3F(~2, ~0x35, ~0x052),	 "9,e,f", 0, v9 },
{ "fcmped",	          F3F(2, 0x35, 0x056),            F3F(~2, ~0x35, ~0x056)|RS1_G0, "e,f",   0, v6 },
{ "fcmped",	CMPFCC(0)|F3F(2, 0x35, 0x056), CMPFCC(~0)|F3F(~2, ~0x35, ~0x056),	 "6,e,f", 0, v9 },
{ "fcmped",	CMPFCC(1)|F3F(2, 0x35, 0x056), CMPFCC(~1)|F3F(~2, ~0x35, ~0x056),	 "7,e,f", 0, v9 },
{ "fcmped",	CMPFCC(2)|F3F(2, 0x35, 0x056), CMPFCC(~2)|F3F(~2, ~0x35, ~0x056),	 "8,e,f", 0, v9 },
{ "fcmped",	CMPFCC(3)|F3F(2, 0x35, 0x056), CMPFCC(~3)|F3F(~2, ~0x35, ~0x056),	 "9,e,f", 0, v9 },
{ "fcmpeq",	          F3F(2, 0x34, 0x057),            F3F(~2, ~0x34, ~0x057),	 "e,f,g", 0, v8 },
{ "fcmpeq",	CMPFCC(0)|F3F(2, 0x35, 0x057), CMPFCC(~0)|F3F(~2, ~0x35, ~0x057),	 "6,e,f", 0, v9 },
{ "fcmpeq",	CMPFCC(1)|F3F(2, 0x35, 0x057), CMPFCC(~1)|F3F(~2, ~0x35, ~0x057),	 "7,e,f", 0, v9 },
{ "fcmpeq",	CMPFCC(2)|F3F(2, 0x35, 0x057), CMPFCC(~2)|F3F(~2, ~0x35, ~0x057),	 "8,e,f", 0, v9 },
{ "fcmpeq",	CMPFCC(3)|F3F(2, 0x35, 0x057), CMPFCC(~3)|F3F(~2, ~0x35, ~0x057),	 "9,e,f", 0, v9 },
{ "fcmpes",	          F3F(2, 0x35, 0x055),            F3F(~2, ~0x35, ~0x055)|RS1_G0, "e,f",   0, v6 },
{ "fcmpes",	CMPFCC(0)|F3F(2, 0x35, 0x055), CMPFCC(~0)|F3F(~2, ~0x35, ~0x055),	 "6,e,f", 0, v9 },
{ "fcmpes",	CMPFCC(1)|F3F(2, 0x35, 0x055), CMPFCC(~1)|F3F(~2, ~0x35, ~0x055),	 "7,e,f", 0, v9 },
{ "fcmpes",	CMPFCC(2)|F3F(2, 0x35, 0x055), CMPFCC(~2)|F3F(~2, ~0x35, ~0x055),	 "8,e,f", 0, v9 },
{ "fcmpes",	CMPFCC(3)|F3F(2, 0x35, 0x055), CMPFCC(~3)|F3F(~2, ~0x35, ~0x055),	 "9,e,f", 0, v9 },
{ "fcmpex",	          F3F(2, 0x35, 0x057),            F3F(~2, ~0x35, ~0x057)|RS1_G0, "e,f",   0, cypress },
{ "fcmpq",	          F3F(2, 0x34, 0x053),            F3F(~2, ~0x34, ~0x053),	 "e,f,g", 0, v8 },
{ "fcmpq",	CMPFCC(0)|F3F(2, 0x35, 0x053), CMPFCC(~0)|F3F(~2, ~0x35, ~0x053),	 "6,e,f", 0, v9 },
{ "fcmpq",	CMPFCC(1)|F3F(2, 0x35, 0x053), CMPFCC(~1)|F3F(~2, ~0x35, ~0x053),	 "7,e,f", 0, v9 },
{ "fcmpq",	CMPFCC(2)|F3F(2, 0x35, 0x053), CMPFCC(~2)|F3F(~2, ~0x35, ~0x053),	 "8,e,f", 0, v9 },
{ "fcmpq",	CMPFCC(3)|F3F(2, 0x35, 0x053), CMPFCC(~3)|F3F(~2, ~0x35, ~0x053),	 "9,e,f", 0, v9 },
{ "fcmps",	          F3F(2, 0x35, 0x051),            F3F(~2, ~0x35, ~0x051)|RS1_G0, "e,f",   0, v6 },
{ "fcmps",	CMPFCC(0)|F3F(2, 0x35, 0x051), CMPFCC(~0)|F3F(~2, ~0x35, ~0x051),	 "6,e,f", 0, v9 },
{ "fcmps",	CMPFCC(1)|F3F(2, 0x35, 0x051), CMPFCC(~1)|F3F(~2, ~0x35, ~0x051),	 "7,e,f", 0, v9 },
{ "fcmps",	CMPFCC(2)|F3F(2, 0x35, 0x051), CMPFCC(~2)|F3F(~2, ~0x35, ~0x051),	 "8,e,f", 0, v9 },
{ "fcmps",	CMPFCC(3)|F3F(2, 0x35, 0x051), CMPFCC(~3)|F3F(~2, ~0x35, ~0x051),	 "9,e,f", 0, v9 },
{ "fcmpx",	          F3F(2, 0x35, 0x053),            F3F(~2, ~0x35, ~0x053)|RS1_G0, "e,f",   0, cypress },

{ "cpop1",	F3(2, 0x36, 0), F3(~2, ~0x36, ~1), "[1+2],d", 0, v6 },
{ "cpop2",	F3(2, 0x37, 0), F3(~2, ~0x37, ~1), "[1+2],d", 0, v6 },
    
{ "casx",	F3(3, 0x0c, 1), F3(~3, ~0x0c, ~1), "[1],2,d", 0, v9 },
{ "casxa",	F3(3, 0x1c, 1), F3(~3, ~0x1c, ~1), "[1]A,2,d", 0, v9 },
{ "cas",	F3(3, 0x0c, 0), F3(~3, ~0x0c, ~0), "[1],2,d", 0, v9 },
{ "casa",	F3(3, 0x1c, 0), F3(~3, ~0x1c, ~0), "[1]A,2,d", 0, v9 },

{ "fmaddd",	F3(2, 0x35, 0)|OPF_LOW(0xa), F3(~2, ~0x35, ~0)|OPF_LOW(~0xa), "e,f,j,g", 0, v9 },
{ "fmaddq",	F3(2, 0x35, 0)|OPF_LOW(0xb), F3(~2, ~0x35, ~0)|OPF_LOW(~0xb), "e,f,j,g", 0, v9 },
{ "fmadds",	F3(2, 0x35, 0)|OPF_LOW(0x9), F3(~2, ~0x35, ~0)|OPF_LOW(~0x9), "e,f,j,g", 0, v9 },
{ "fmsubd",	F3(2, 0x35, 0)|OPF_LOW(0xe), F3(~2, ~0x35, ~0)|OPF_LOW(~0xe), "e,f,j,g", 0, v9 },
{ "fmsubq",	F3(2, 0x35, 0)|OPF_LOW(0xf), F3(~2, ~0x35, ~0)|OPF_LOW(~0xf), "e,f,j,g", 0, v9 },
{ "fmsubs",	F3(2, 0x35, 0)|OPF_LOW(0xd), F3(~2, ~0x35, ~0)|OPF_LOW(~0xd), "e,f,j,g", 0, v9 },

};

#define NUMOPCODES ((sizeof sparc_opcodes)/(sizeof sparc_opcodes[0]))

/*
 * Local Variables:
 * fill-column: 131
 * comment-column: 0
 * End:
 */

/* end of sparc-opcode.h */
