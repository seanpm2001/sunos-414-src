/*	@(#)opdescr.h 1.1 94/10/31 SMI	*/

/*
 * Copyright (c) 1986 by Sun Microsystems, Inc.
 */
#ifndef lint
static char RELEASE[] = "@(#)RELEASE SunOS compilers 4.1";
#endif

/*
 * This table gives the names, properties and register "weights" of ir
 *	operators - see also the op_map_tab in /lib/cgrdr/pcc.c.
 *	It must consistent with the enum IR_OP in ir_common.h.
*/
struct opdescr_st op_descr[] =	{
#if TARGET == MC68000
	{"err", HOUSE_OP,
		{0, 0}, {0, 0}, 0},
	{"entry_def", UN_OP | HOUSE_OP | MOD_OP | BOOL_OP | FLOAT_OP,
		{-12, -12}, {0, 0}, -60},
	{"exit_use", UN_OP | USE1_OP | HOUSE_OP | BOOL_OP | FLOAT_OP,
		{-12, -12}, {0, 0}, -60}, 
	{"implicit_def", UN_OP | HOUSE_OP | MOD_OP | BOOL_OP | FLOAT_OP,
		{-12, -12}, {0, 0}, -60},
	{"implicit_use", UN_OP | HOUSE_OP | USE1_OP | BOOL_OP | FLOAT_OP,
		{-12, -12}, {0, 0}, -60},
	{"plus", BIN_OP | VALUE_OP | USE1_OP | USE2_OP | FLOAT_OP | COMMUTE_OP,
		{12, 12}, {12, 12}, 30},
	{"minus", BIN_OP | VALUE_OP | USE1_OP | USE2_OP | FLOAT_OP,
		{12, 12}, {12, 8}, 30},
	{"mult", BIN_OP | VALUE_OP | USE1_OP | USE2_OP | FLOAT_OP | COMMUTE_OP,
		{12, 12}, {12, 12}, 30},
 	{"div", BIN_OP | VALUE_OP | USE1_OP | USE2_OP | FLOAT_OP,
		{12, 12}, {12, 12}, 30},
	{"remainder", BIN_OP | VALUE_OP | USE1_OP | USE2_OP | FLOAT_OP,
		{12, 12}, {12, 12}, 30},
	{"and", BIN_OP | VALUE_OP | USE1_OP | USE2_OP | BOOL_OP | COMMUTE_OP,
		{12, 8}, {12, 8}, -60},
	{"or", BIN_OP | VALUE_OP | USE1_OP | USE2_OP | BOOL_OP | COMMUTE_OP,
		{12, 8}, {12, 8}, -60},
	{"xor", BIN_OP | VALUE_OP | USE1_OP | USE2_OP | BOOL_OP | COMMUTE_OP,
		{12, 8}, {12, 8}, -60},
	{"not", UN_OP | VALUE_OP | USE1_OP | BOOL_OP,
		{12, 8}, {0, 0}, -60},
	{"lshift", BIN_OP | VALUE_OP | USE1_OP | USE2_OP,
		{14, 10}, {14, 10}, -60},
	{"rshift", BIN_OP | VALUE_OP | USE1_OP | USE2_OP,
		{14, 10}, {14, 10}, -60},
	{"scall", BIN_OP | ROOT_OP | USE1_OP | NTUPLE_OP,
		{0, 0}, {0, 0}, 0},
	{"fcall", BIN_OP | VALUE_OP |  USE1_OP | FLOAT_OP | NTUPLE_OP,
		{0, 0}, {0, 0}, 0},
	{"eq", BIN_OP | VALUE_OP | USE1_OP | USE2_OP | BOOL_OP | FLOAT_OP | COMMUTE_OP,
		{12, 8}, {12, 8}, 30},
	{"ne", BIN_OP | VALUE_OP | USE1_OP | USE2_OP | BOOL_OP | FLOAT_OP | COMMUTE_OP,
		{12, 8}, {12, 8}, 30},
	{"le", BIN_OP | VALUE_OP | USE1_OP | USE2_OP | BOOL_OP | FLOAT_OP ,
		{12, 8}, {12, 8}, 30},
	{"lt", BIN_OP | VALUE_OP | USE1_OP | USE2_OP | BOOL_OP | FLOAT_OP ,
		{12, 8}, {12, 8}, 30},
	{"ge", BIN_OP | VALUE_OP | USE1_OP | USE2_OP | BOOL_OP | FLOAT_OP ,
		{12, 8}, {12, 8}, 30},
	{"gt", BIN_OP | VALUE_OP | USE1_OP | USE2_OP | BOOL_OP | FLOAT_OP ,
		{12, 8}, {12, 8}, 30},
	{"conv", UN_OP | VALUE_OP | USE1_OP | FLOAT_OP | BOOL_OP ,
		{12, 8}, {0, 0}, 30},
	{"compl", UN_OP | VALUE_OP | USE1_OP | BOOL_OP ,
		{12, 8}, {0, 0}, 30},
	{"neg", UN_OP | VALUE_OP | USE1_OP | FLOAT_OP ,
		{18, 14}, {0, 0}, 30},
	{"addrof", UN_OP | VALUE_OP  ,
		{-1000000, -1000000}, {-1000000, -100000}, -100000 },
	{"ifetch", UN_OP | VALUE_OP | USE1_OP | FLOAT_OP | BOOL_OP ,
		{8, 12}, {0, 0}, -60},
	{"istore", BIN_OP | MOD_OP | USE1_OP | USE2_OP | FLOAT_OP | BOOL_OP | ROOT_OP,
		{8, 12}, {12, 12}, 30},
	{"goto", UN_OP | BRANCH_OP | ROOT_OP  | NTUPLE_OP,
		{8, 12}, {0, 0}, -60},
	{"cbranch", BIN_OP | BRANCH_OP | USE1_OP | BOOL_OP | ROOT_OP  | NTUPLE_OP,
		{12, 8}, {8, 12}, 30},
	{"switch", BIN_OP | BRANCH_OP | USE1_OP | ROOT_OP  | NTUPLE_OP,
		{12, 12}, {8, 12}, 30},
	{"repeat", BIN_OP | BRANCH_OP | USE1_OP | MOD_OP | ROOT_OP  | NTUPLE_OP,
		{22, 8}, {0, 0}, -60},
	{"assign", BIN_OP | MOD_OP | USE2_OP | BOOL_OP | FLOAT_OP | ROOT_OP  ,
		{12, 12}, {12, 12}, 30},
	{"pass", UN_OP | HOUSE_OP  ,
		{0, 0}, {0, 0}, 0},
	{"stmt", BIN_OP | HOUSE_OP  ,
		{0, 0}, {0, 0}, 0},
	{"labeldef", UN_OP | ROOT_OP,
		{0, 0}, {0, 0}, 0},
	{"indirgoto", UN_OP | BRANCH_OP | USE1_OP | ROOT_OP  | NTUPLE_OP ,
		{8, 12}, {0, 0}, 0},
	{"fval", UN_OP | ROOT_OP | USE1_OP  ,
		{16, 8}, {0, 0}, 0},
	{"labelref", BIN_OP | HOUSE_OP  ,
		{0, 0}, {0, 0}, 0},
	{"param", UN_OP | USE1_OP  ,
		{12, 12}, {0, 0}, 30},
	{"pconv", UN_OP | VALUE_OP | USE1_OP ,
		{8, 12}, {0, 0}, 0},
	{"foreff", UN_OP | ROOT_OP | USE1_OP ,
		{0, 0}, {0, 0}, 0},
#endif

#if TARGET == SPARC
/*
 * On Sparc there are integer registers and floating point registers.
 * Left and right should have same benefit for Sparc, so always use
 * left.d_weight and f_weight;
 */

	{"err", HOUSE_OP,
		{0, 0}, {0, 0}, 0},
	{"entry_def", UN_OP | HOUSE_OP | MOD_OP | BOOL_OP | FLOAT_OP,
		{-3, 0}, {0, 0}, -3},
	{"exit_use", UN_OP | USE1_OP | HOUSE_OP | BOOL_OP | FLOAT_OP,
		{-3, 0}, {0, 0}, -3}, 
	{"implicit_def", UN_OP | HOUSE_OP | MOD_OP | BOOL_OP | FLOAT_OP,
		{-3, 0}, {0, 0}, -3},
	{"implicit_use", UN_OP | HOUSE_OP | USE1_OP | BOOL_OP | FLOAT_OP,
		{-3, 0}, {0, 0}, -3},
	{"plus", BIN_OP | VALUE_OP | USE1_OP | USE2_OP | FLOAT_OP | COMMUTE_OP,
		{2, 0}, {0, 0}, 2},
	{"minus", BIN_OP | VALUE_OP | USE1_OP | USE2_OP | FLOAT_OP,
		{2, 0}, {0, 0}, 2},
	{"mult", BIN_OP | VALUE_OP | USE1_OP | USE2_OP | FLOAT_OP | COMMUTE_OP,
		{2, 0}, {0, 0}, 2},
 	{"div", BIN_OP | VALUE_OP | USE1_OP | USE2_OP | FLOAT_OP,
		{2, 0}, {0, 0}, 2},
	{"remainder", BIN_OP | VALUE_OP | USE1_OP | USE2_OP | FLOAT_OP,
		{2, 0}, {0, 0}, 2},
	{"and", BIN_OP | VALUE_OP | USE1_OP | USE2_OP | BOOL_OP | COMMUTE_OP,
		{2, 0}, {0, 0}, 0},
	{"or", BIN_OP | VALUE_OP | USE1_OP | USE2_OP | BOOL_OP | COMMUTE_OP,
		{2, 0}, {0, 0}, 0},
	{"xor", BIN_OP | VALUE_OP | USE1_OP | USE2_OP | BOOL_OP | COMMUTE_OP,
		{2, 0}, {0, 0}, 0},
	{"not", UN_OP | VALUE_OP | USE1_OP | BOOL_OP,
		{2, 0}, {0, 0}, 0},
	{"lshift", BIN_OP | VALUE_OP | USE1_OP | USE2_OP,
		{2, 0}, {0, 0}, 0},
	{"rshift", BIN_OP | VALUE_OP | USE1_OP | USE2_OP,
		{2, 0}, {0, 0}, 0},
	{"scall", BIN_OP | ROOT_OP | USE1_OP | NTUPLE_OP,
		{0, 0}, {0, 0}, 0},
	{"fcall", BIN_OP | VALUE_OP |  USE1_OP | FLOAT_OP | NTUPLE_OP,
		{0, 0}, {0, 0}, 0},
	{"eq", BIN_OP | VALUE_OP | USE1_OP | USE2_OP | BOOL_OP | FLOAT_OP | COMMUTE_OP,
		{2, 0}, {0, 0}, 2},
	{"ne", BIN_OP | VALUE_OP | USE1_OP | USE2_OP | BOOL_OP | FLOAT_OP | COMMUTE_OP,
		{2, 0}, {0, 0}, 2},
	{"le", BIN_OP | VALUE_OP | USE1_OP | USE2_OP | BOOL_OP | FLOAT_OP ,
		{2, 0}, {0, 0}, 2},
	{"lt", BIN_OP | VALUE_OP | USE1_OP | USE2_OP | BOOL_OP | FLOAT_OP ,
		{2, 0}, {0, 0}, 2},
	{"ge", BIN_OP | VALUE_OP | USE1_OP | USE2_OP | BOOL_OP | FLOAT_OP ,
		{2, 0}, {0, 0}, 2},
	{"gt", BIN_OP | VALUE_OP | USE1_OP | USE2_OP | BOOL_OP | FLOAT_OP ,
		{2, 0}, {0, 0}, 2},
	{"conv", UN_OP | VALUE_OP | USE1_OP | FLOAT_OP | BOOL_OP ,
		{2, 0}, {0, 0}, 2},
	{"compl", UN_OP | VALUE_OP | USE1_OP | BOOL_OP ,
		{2, 0}, {0, 0}, 2},
	{"neg", UN_OP | VALUE_OP | USE1_OP | FLOAT_OP ,
		{2, 0}, {0, 0}, 2},
	{"addrof", UN_OP | VALUE_OP  ,
		{-1000000, -1000000}, {-1000000, -1000000}, -1000000},
	{"ifetch", UN_OP | VALUE_OP | USE1_OP | FLOAT_OP | BOOL_OP ,
		{2, 0}, {0, 0}, 0},
	{"istore", BIN_OP | MOD_OP | USE1_OP | USE2_OP | FLOAT_OP | BOOL_OP | ROOT_OP,
		{2, 0}, {0, 0}, 0},
	{"goto", UN_OP | BRANCH_OP | ROOT_OP  | NTUPLE_OP,
		{2, 0}, {0, 0}, 0},
	{"cbranch", BIN_OP | BRANCH_OP | USE1_OP | BOOL_OP | ROOT_OP  | NTUPLE_OP,
		{2, 0}, {0, 0}, 2},
	{"switch", BIN_OP | BRANCH_OP | USE1_OP | ROOT_OP  | NTUPLE_OP,
		{2, 0}, {0, 0}, 2},
	{"repeat", BIN_OP | BRANCH_OP | USE1_OP | MOD_OP | ROOT_OP  | NTUPLE_OP,
		{0, 0}, {0, 0}, 0},
	{"assign", BIN_OP | MOD_OP | USE2_OP | BOOL_OP | FLOAT_OP | ROOT_OP  ,
		{3, 0}, {0, 0}, 3},
	{"pass", UN_OP | HOUSE_OP  ,
		{0, 0}, {0, 0}, 0},
	{"stmt", BIN_OP | HOUSE_OP  ,
		{0, 0}, {0, 0}, 0},
	{"labeldef", UN_OP | ROOT_OP,
		{0, 0}, {0, 0}, 0},
	{"indirgoto", UN_OP | BRANCH_OP | USE1_OP | ROOT_OP  | NTUPLE_OP ,
		{2, 0}, {0, 0}, 0},
	{"fval", UN_OP | ROOT_OP | USE1_OP  ,
		{2, 0}, {0, 0}, 0},
	{"labelref", BIN_OP | HOUSE_OP  ,
		{0, 0}, {0, 0}, 0},
	{"param", UN_OP | USE1_OP  ,
		{2, 0}, {0, 0}, 3},
	{"pconv", UN_OP | VALUE_OP | USE1_OP ,
		{2, 0}, {0, 0}, 0},
	{"foreff", UN_OP | ROOT_OP | USE1_OP ,
		{0, 0}, {0, 0}, 0},
#endif
#if TARGET == I386
/*
 * On the 386 there are integer registers and floating point registers.
 * Left and right usually have the same benefit, so always use
 * left.{d,a}_weight and f_weight.
 */

	{"err", HOUSE_OP,
		{0, 0}, {0, 0}, 0},
	{"entry_def", UN_OP | HOUSE_OP | MOD_OP | BOOL_OP | FLOAT_OP,
		{-4, -4}, {0, 0}, -37},
	{"exit_use", UN_OP | USE1_OP | HOUSE_OP | BOOL_OP | FLOAT_OP,
		{-2, -2}, {0, 0}, -59}, 
	{"implicit_def", UN_OP | HOUSE_OP | MOD_OP | BOOL_OP | FLOAT_OP,
		{-4, -4}, {0, 0}, -37},
	{"implicit_use", UN_OP | HOUSE_OP | USE1_OP | BOOL_OP | FLOAT_OP,
		{-2, -2}, {0, 0}, -59},
	{"plus", BIN_OP | VALUE_OP | USE1_OP | USE2_OP | FLOAT_OP | COMMUTE_OP,
		{4,  4}, {0, 0}, 6},
	{"minus", BIN_OP | VALUE_OP | USE1_OP | USE2_OP | FLOAT_OP,
		{4, 4}, {0, 0}, 2},
	{"mult", BIN_OP | VALUE_OP | USE1_OP | USE2_OP | FLOAT_OP | COMMUTE_OP,
		{3, 3}, {0, 0}, 2},
 	{"div", BIN_OP | VALUE_OP | USE1_OP | USE2_OP | FLOAT_OP,
		{3, 3}, {0, 0}, 6},
	{"remainder", BIN_OP | VALUE_OP | USE1_OP | USE2_OP | FLOAT_OP,
		{3, 3}, {0, 0}, 11},
	{"and", BIN_OP | VALUE_OP | USE1_OP | USE2_OP | BOOL_OP | COMMUTE_OP,
		{4, 4}, {0, 0}, 0},
	{"or", BIN_OP | VALUE_OP | USE1_OP | USE2_OP | BOOL_OP | COMMUTE_OP,
		{4, 4}, {0, 0}, 0},
	{"xor", BIN_OP | VALUE_OP | USE1_OP | USE2_OP | BOOL_OP | COMMUTE_OP,
		{4, 4}, {0, 0}, 0},
	{"not", UN_OP | VALUE_OP | USE1_OP | BOOL_OP,
		{4, 4}, {0, 0}, 0},
	{"lshift", BIN_OP | VALUE_OP | USE1_OP | USE2_OP,
		{4, 4}, {0, 0}, 0},
	{"rshift", BIN_OP | VALUE_OP | USE1_OP | USE2_OP,
		{4, 4}, {0, 0}, 0},
	{"scall", BIN_OP | ROOT_OP | USE1_OP | NTUPLE_OP,
		{0, 0}, {0, 0}, 0},
	{"fcall", BIN_OP | VALUE_OP |  USE1_OP | FLOAT_OP | NTUPLE_OP,
		{0, 0}, {0, 0}, 0},
	{"eq", BIN_OP | VALUE_OP | USE1_OP | USE2_OP | BOOL_OP | FLOAT_OP | COMMUTE_OP,
		{3, 3}, {0, 0}, 7},
	{"ne", BIN_OP | VALUE_OP | USE1_OP | USE2_OP | BOOL_OP | FLOAT_OP | COMMUTE_OP,
		{3, 3}, {0, 0}, 7},
	{"le", BIN_OP | VALUE_OP | USE1_OP | USE2_OP | BOOL_OP | FLOAT_OP ,
		{3, 3}, {0, 0}, 7},
	{"lt", BIN_OP | VALUE_OP | USE1_OP | USE2_OP | BOOL_OP | FLOAT_OP ,
		{3, 3}, {0, 0}, 7},
	{"ge", BIN_OP | VALUE_OP | USE1_OP | USE2_OP | BOOL_OP | FLOAT_OP ,
		{3, 3}, {0, 0}, 7},
	{"gt", BIN_OP | VALUE_OP | USE1_OP | USE2_OP | BOOL_OP | FLOAT_OP ,
		{3, 3}, {0, 0}, 7},
	{"conv", UN_OP | VALUE_OP | USE1_OP | FLOAT_OP | BOOL_OP ,
		{4, 4}, {0, 0}, 11},
	{"compl", UN_OP | VALUE_OP | USE1_OP | BOOL_OP ,
		{4, 4}, {0, 0}, -59},
	{"neg", UN_OP | VALUE_OP | USE1_OP | FLOAT_OP ,
		{4, 4}, {0, 0}, 11},
	{"addrof", UN_OP | VALUE_OP  ,
		{-1000000, -1000000}, {-1000000, -1000000}, -1000000},
	{"ifetch", UN_OP | VALUE_OP | USE1_OP | FLOAT_OP | BOOL_OP ,
		{4, 4}, {0, 0}, 0},
	{"istore", BIN_OP | MOD_OP | USE1_OP | USE2_OP | FLOAT_OP | BOOL_OP | ROOT_OP,
		{4, 4}, {0, 0}, 0},
	{"goto", UN_OP | BRANCH_OP | ROOT_OP  | NTUPLE_OP,
		{3, 3}, {0, 0}, 0},
	{"cbranch", BIN_OP | BRANCH_OP | USE1_OP | BOOL_OP | ROOT_OP  | NTUPLE_OP,
		{4, 4}, {0, 0}, 11},
	{"switch", BIN_OP | BRANCH_OP | USE1_OP | ROOT_OP  | NTUPLE_OP,
		{4, 4}, {0, 0}, 11},
	{"repeat", BIN_OP | BRANCH_OP | USE1_OP | MOD_OP | ROOT_OP  | NTUPLE_OP,
		{2, 2}, {0, 0}, 0},
	{"assign", BIN_OP | MOD_OP | USE2_OP | BOOL_OP | FLOAT_OP | ROOT_OP  ,
		{4, 4}, {0, 0}, 33},
	{"pass", UN_OP | HOUSE_OP  ,
		{0, 0}, {0, 0}, 0},
	{"stmt", BIN_OP | HOUSE_OP  ,
		{0, 0}, {0, 0}, 0},
	{"labeldef", UN_OP | ROOT_OP,
		{0, 0}, {0, 0}, 0},
	{"indirgoto", UN_OP | BRANCH_OP | USE1_OP | ROOT_OP  | NTUPLE_OP ,
		{3, 3}, {0, 0}, 0},
	{"fval", UN_OP | ROOT_OP | USE1_OP  ,
		{4, 4}, {0, 0}, 11},
	{"labelref", BIN_OP | HOUSE_OP  ,
		{0, 0}, {0, 0}, 0},
	{"param", UN_OP | USE1_OP  ,
		{3, 3}, {0, 0}, -49},
	{"pconv", UN_OP | VALUE_OP | USE1_OP ,
		{4, 4}, {0, 0}, 0},
	{"foreff", UN_OP | ROOT_OP | USE1_OP ,
		{0, 0}, {0, 0}, 0},
#endif
};