/* @(#)genpercpu.c 1.1 94/10/31 SMI */

/*
 * Copyright (c) 1989, Sun Microsystems
 *
 * This file generates the assembly code file that places
 * the per-cpu data staticly in the correct locations,
 * and the include files for C source that present the
 * proper definitions for the symbols and a structure that
 * maps them for access via the mappings to the other
 * processors' percpu areas.
 */
#include <stdio.h>
#include <sys/user.h>
#include <sys/proc.h>
#include <os/atom.h>
#include <machine/param.h>
#include <machine/mmu.h>
#include <machine/devaddr.h>
#include <machine/clock.h>
#include <machine/intreg.h>
#include <machine/scb.h>
#include <machine/async.h>
#include <vm/seg.h>
#include <sys/ieeefp.h>

#ifndef	INTSTACKSIZE
#define	INTSTACKSIZE	(3 * PAGESIZE)
#endif

#define	PCPUELT(a,t,n,e,b) { a, "t", "n", sizeof (t), e, "e", b }

#define	ST	struct

struct {
	int	    align;
	char	   *type;
	char	   *name;
	int	    size;
	int	    elts;
	char	   *stxt;
	int	    back;
} percpudef[] = {
/*	Alignment	BasicType	Name	     Array Elts     Backup */
#ifdef	MULTIPROCESSOR
PCPUELT(    4096,	char,		intstack,	INTSTACKSIZE,	0),
PCPUELT(    4096,	char,		exitstack,	INTSTACKSIZE,	0),
PCPUELT(       4,	char,		eintstack,	1,              1),
PCPUELT(    4096,	char,		kernstack,	KERNSTACK,      0),
PCPUELT(       4,	char,		eexitstack,	1,              1),
PCPUELT(       4,    ST seguser,	_ubasic,	0,              1),
PCPUELT(    4096,    ST user,		_idleuarea,	0,              0),
PCPUELT(       4,	char,		ekernstack,	1,              1),
PCPUELT(       4,    ST proc,		_idleproc,	0,              0),
PCPUELT(       4,    ST user,		intu,		0,              0),

PCPUELT(      32, 	int,		_bcopy_res,	0,              0),
PCPUELT(      32, 	int,		_cpuid,		0,              0),
PCPUELT(       4, 	int,		_cpu_enable,	0,              0),
PCPUELT(       4, 	int,		_cpu_exists,	0,              0),
PCPUELT(       4,	int,		_cpu_idle,	0,		0),
PCPUELT(       4,	int,		_cpu_supv,	0,		0),
PCPUELT(       4,	int,		_Cpudelay,	0,		0),
PCPUELT(       4,	u_char *,	_prom_mailbox,	0,		0),

PCPUELT(      32,    ST user *,		_uunix,		0,              0),
PCPUELT(       4,    ST proc *,		_masterprocp,	0,              0),
PCPUELT(       4, 	int,		_noproc,	0,              0),
PCPUELT(       4,	int,		_runrun,	0,		0),
PCPUELT(       1,	char,		_curpri,	0,		0),

PCPUELT(      32,	atom_t,		_xc_doit,	0,		0),
PCPUELT(       4,	atom_t,		_xc_busy,	0,		0),
PCPUELT(       8,	u_int,		mulchksave,	3,		0),

PCPUELT(      32,    ST fp *,		_fp_ctxp,	0,		0),
PCPUELT(      32,	label_t,	_panic_label,	0,		0),

PCPUELT(      32,	atom_t,		_aflt_sync,	0,		0),
PCPUELT(       4,	int,		_a_head,	0,		0),
PCPUELT(       4,	int,		_a_tail,	0,		0),
PCPUELT(       4, ST async_flt,		_sys_fatal_flt,	0,		0),
PCPUELT(       4, ST async_flt,		_a_flts,	MAX_AFLTS,	0),
#endif	MULTIPROCESSOR

PCPUELT(    4096,	char,		epcpumem,	1,		0),
/*
 * note: since utimers does not backup, we get a one-page deadzone.
 * forcing the alignment of "utimers" makes it at a fixed address
 * independent of whether MP is specified, as long as the MP
 * data area is not larger than utimers' alignment.
 */
PCPUELT( 32*4096,    ST count14,	_utimers,	0,		0),
PCPUELT(    4096,    ST cpu_intreg,	_intregs,	0,		0),
PCPUELT(    4096,    ST scb,		_vscb,		0,		0),
	{ 0, "", "", 0, 0, "" },
};

static char *
sbf(p)
	char *p;
{
	while (p && *p && ((*p == ' ') || (*p == '\t')))
		++p;
	return p;
}

static char version[] = "genpercpu.c version 1.1 updated 94/10/31";

static char header[] = "/* %s\tcreated %s * This file automaticly generated by\n * %s;\n * any changes you make to it WILL BE LOST.\n */\n";

/*
 * outputs:
 *	<stdout>	abs location declarations
 *	percpu_ext.h	extern decls for percpu vars
 *	percpu_str.h	strucure declaration
 *	percpu_def.h	various useful #defines
 */
main()
{
	int align, size, elts, i, j, here, fill, back, now;
	int	mem_addr;	/* current address in memory */
	int	str_addr;	/* current address in structure */
	int	epcpumem_offset;
	char *type, *name, *stxt;
	FILE *fx, *fs, *fd;

	now = time(0);

	fx = fopen("percpu.h", "w");
	fs = fopen("percpu_str.h", "w");
	fd = fopen("percpu_def.h", "w");

	fprintf(fx, header, "percpu.h", ctime(&now), version);
	fprintf(fs, header, "percpu_str.h", ctime(&now), version);
	fprintf(fd, header, "percpu_def.h", ctime(&now), version);
	printf(header, "percpu.s", ctime(&now), version);

	fprintf(fd, "%s\n", "#include <os/atom.h>");
	fprintf(fd, "%s\n", "#include <machine/devaddr.h>");
	fprintf(fd, "%s\n", "#include <machine/clock.h>");
	fprintf(fd, "%s\n", "#include <machine/intreg.h>");
	fprintf(fd, "%s\n", "#include <machine/scb.h>");
	fprintf(fd, "%s\n", "#include <machine/async.h>");
	fprintf(fd, "#ifndef	LOCORE\n\n");
	fprintf(fd, "%s\n", "#include <sys/ieeefp.h>");
	fprintf(fd, "%s\n", "#include <vm/seg.h>");
	fprintf(fd, "#endif	!LOCORE\n\n");

	fprintf(fs, "%s\n", "#include \"percpu_def.h\"");
	fprintf(fx, "%s\n", "#include \"percpu_str.h\"");
	printf("%s\n", "#include \"percpu_def.h\"");

	fprintf(fs, "\n#define ST struct\n\n");
	fprintf(fx, "\n#define ST struct\n\n");

	printf("\t.global _PerCPU\n_PerCPU = VA_PERCPU\n");
	fprintf(fs,"extern struct PerCPU {\n");
	here = mem_addr = str_addr = fill = 0;
	epcpumem_offset = 0;

	for (i=0; percpudef[i].align; ++i) {
		align = percpudef[i].align;
		type = sbf(percpudef[i].type);
		name = sbf(percpudef[i].name);
		size = percpudef[i].size;
		elts = percpudef[i].elts;
		stxt = sbf(percpudef[i].stxt);
		back = percpudef[i].back;

		if (*name == '_')
			fprintf(fx,"extern %-16s %s", type, name+1);

		if (!back) here = mem_addr;

		if (fill = (here % align))
			here += align - fill;

		printf("\t.global %s\n%s = VA_PERCPUME+PC_%s\n",
			name, name, (*name=='_') ? name+1 : name);
#ifdef	PROVIDE_SYMBOLS
		for (j=0; j<NCPU; ++j)
			printf("c%d_%s = VA_PERCPU+0x%06x+PC_%s\n",
			       j, name, j<<PERCPU_SHIFT,
			       (*name=='_') ? name+1 : name);
#endif	PROVIDE_SYMBOLS
		fprintf(fd, "#define PC_%-15s 0x%x\n",
			(*name=='_') ? name+1 : name, here);

		if (!strcmp(name, "epcpumem")) /* magic cookie */
			epcpumem_offset = here;

		if (!back) {
			if (str_addr != here) {
				fprintf(fs,"\t%-14s _f%d_[0x%x];\n",
					"char", i, here - str_addr);
				str_addr = here;
			}
			fprintf(fs,"\t%-14s %s", type,
				(*name=='_') ? name+1 : name);
		}
		if (elts && stxt && *stxt) {
			if (!back) fprintf(fs,"[%s]", stxt);
			if (*name == '_') fprintf(fx,"[%s]", stxt);
			size *= elts;
		}
		if (!back) str_addr += size;
		size += here;
		if (!back) mem_addr = size;
		if (!back) fprintf(fs,";\n");
		if (*name == '_') fprintf(fx,";\n");
	}

	fprintf(fs,"\tchar           _fill_[0x%x];\n", PERCPUSIZE - str_addr);
	fprintf(fs,"} PerCPU[NCPU];\n");
	fprintf(fd,"#define PERCPU_PAGES %d\n",
		(epcpumem_offset+PAGESIZE-1)/PAGESIZE);
	fprintf(fd,"#define PERCPU_MAPS %d\n",
		(mem_addr+PAGESIZE-1)/PAGESIZE);
	fprintf(fs, "\n#undef ST\n");
	fprintf(fx, "\n#undef ST\n");
	return 0;
}