/* link: -lpcre -lreadline -lm  */
#include <stdlib.h>
#include <string.h>
#include <pcre.h>
#include <ctype.h>
#include <stdio.h>
#include "readline/readline.h"
#include "readline/history.h"
#include <stdint.h>
#include <math.h>

typedef int bool;
#define true 1
#define false 0

#define GOTO_last -1
#define GOTO_next -2
#define GOTO_redo -3
#define GOTO_return -4
#define SVf_const 0
#define SVf_register 1
#define SVf_var 2
#define OP_NOOP 0
#define OP_SEQ 0x100
#define OP_LIST 0x200
#define OP_CONST 0x300
#define OP_CV 0x400
#define OP_block 0x500
#define OP_GOTO_LABEL 0x600
#define OP_GOTO 0x700
#define OP_BREAK 0x800
#define OP_RETURN 0x900
#define OP_REQUIRE 0xa00
#define OPf_bin 0x1
#define OPf_bin_assign 0x2
#define OPf_bin_rel 0x4
#define OPf_num 0x10
#define OPf_int 0x20
#define Opf_string 0x40
#define Opf_other 0x80
#define OP_Plus 0xb11
#define OP_Minus 0xc11
#define OP_Mult 0xd11
#define OP_Div 0xe11
#define OP_MultMult 0xf11
#define OP_Mod 0x1031
#define OP_Or 0x1131
#define OP_And 0x1231
#define OP_Ctrl 0x1331
#define OP_GtGt 0x1431
#define OP_LtLt 0x1531
#define OP_Dot 0x1641
#define OP_x 0x1741
#define OP_EqEq 0x1815
#define OP_EmarkEq 0x1915
#define OP_Lt 0x1a15
#define OP_Gt 0x1b15
#define OP_LtEq 0x1c15
#define OP_GtEq 0x1d15
#define OP_LtEqGt 0x1e15
#define OP_eq 0x1f45
#define OP_ne 0x2045
#define OP_lt 0x2145
#define OP_gt 0x2245
#define OP_le 0x2345
#define OP_ge 0x2445
#define OP_cmp 0x2545
#define OP_PlusEq 0x2612
#define OP_MinusEq 0x2712
#define OP_MultEq 0x2812
#define OP_DivEq 0x2912
#define OP_ModEq 0x2a32
#define OP_OrEq 0x2b32
#define OP_AndEq 0x2c32
#define OP_CtrlEq 0x2d32
#define OP_GtGtEq 0x2e32
#define OP_LtLtEq 0x2f32
#define OP_DotEq 0x3042
#define OP_or 0x3100
#define OP_and 0x3200
#define OP_UMINUS 0x3300
#define OP_NOT 0x3400
#define OP_GLOBAL 0x3500
#define OP_LOCAL 0x3600
#define OP_MY 0x3700
#define OP_ASSIGN 0x3800
#define OP_SUB 0x3900
#define OP_Fcall 0x3a00
#define OP_IF 0x3b00
#define OP_ELIF 0x3c00
#define OP_ELSE 0x3d00
#define OP_IF_YES 0x3e00
#define OP_IF_NO 0x3f00
#define OP_while 0x4000
#define OP_for 0x4100
#define OP_join 0x4200
#define OP_Re 0x4300
#define OP_ReC 0x4400
#define OP_ReMatch 0x4500
#define OP_ReReplace 0x4600
#define OP_VarMatch 0x4700
#define OP_UNARY 0x4800
#define OP_INC 0x4900
#define OP_DEC 0x4a00
#define OP_FN_LIST 0x4b00
#define OP_FN_1 0x4c00
#define OP_SIGIL 0x4d00
#define OP_ARRAY_INDEX 0x4e00
#define OP_HASH_INDEX 0x4f00
#define CVf_switch 1
#define CVf_loop 2
#define CVf_sub 3
#define HEAP_op 1
#define HEAP_sv 2
#define T_ATOM 1
#define T_BOC 0x106
#define T_BOS 0x206
#define T_EOC 0x30b
#define T_EOF 0x40b
#define T_Semi 0x50c
#define T_or 0x610
#define T_and 0x714
#define T_not 0x81a
#define T_FN_LIST 0x91e
#define T_FN_GOTO 0xa1e
#define T_Comma 0xb20
#define T_Eq 0xc25
#define T_PlusEq 0xd25
#define T_MinusEq 0xe25
#define T_MultEq 0xf25
#define T_DivEq 0x1025
#define T_ModEq 0x1125
#define T_DotEq 0x1225
#define T_OrEq 0x1325
#define T_AndEq 0x1425
#define T_CtrlEq 0x1525
#define T_GtGtEq 0x1625
#define T_LtLtEq 0x1725
#define T_Colon 0x1829
#define T_Qmark 0x1929
#define T_DotDot 0x1a2c
#define T_OrOr 0x1b30
#define T_AndAnd 0x1c34
#define T_Or 0x1d38
#define T_Ctrl 0x1e38
#define T_And 0x1f3c
#define T_EqEq 0x2040
#define T_EmarkEq 0x2140
#define T_LtEqGt 0x2240
#define T_eq 0x2340
#define T_ne 0x2440
#define T_cmp 0x2540
#define T_Lt 0x2644
#define T_Gt 0x2744
#define T_LtEq 0x2844
#define T_GtEq 0x2944
#define T_lt 0x2a44
#define T_gt 0x2b44
#define T_le 0x2c44
#define T_ge 0x2d44
#define T_FN_1 0x2e4a
#define T_GtGt 0x2f4c
#define T_LtLt 0x304c
#define T_Plus 0x3150
#define T_Minus 0x3250
#define T_Dot 0x3350
#define T_Mult 0x3454
#define T_Div 0x3554
#define T_Mod 0x3654
#define T_x 0x3754
#define T_EqTlide 0x3858
#define T_UMINUS 0x395e
#define T_Tlide 0x3a5e
#define T_Emark 0x3b5e
#define T_UAMPER 0x3c5e
#define T_MultMult 0x3d61
#define T_PlusPlus 0x3e66
#define T_MinusMinus 0x3f66
#define T_MinusGt 0x4068
#define T_UNARY 0x416e
#define T_SIGIL 0x426e
#define T_MY 0x436e
#define T_EqGt T_Comma
#define isword(c) (isalnum(c) || c=='_')
#define isword1st(c) (isalpha(c) || c=='_')
#define isoct(c) (c>='0' && c<='8')

enum {SVt_undef, SVt_int, SVt_float,SVt_BASIC,SVt_av, SVt_hv, SVt_sv, SVt_string, SVt_cv, SVt_goto, SVt_io, SVt_regex};
enum WORD {WORD_,WORD_eq,WORD_ne,WORD_le,WORD_ge,WORD_lt,WORD_gt,WORD_cmp,WORD_or,WORD_and,WORD_not,WORD_x,WORD_OPERATOR,WORD_goto,WORD_next,WORD_last,WORD_redo,WORD_return,WORD_FN_GOTO,WORD_print,WORD_printf,WORD_warn,WORD_die,WORD_join,WORD_open,WORD_FN_LIST,WORD_uc,WORD_lc,WORD_ucfirst,WORD_lcfirst,WORD_quotemeta,WORD_close,WORD_fread,WORD_FN_1,WORD_use,WORD_require,WORD_no,WORD_package,WORD_sub,WORD_if,WORD_elsif,WORD_else,WORD_while,WORD_for,WORD_my,WORD_our,WORD_local};

struct AV {
    struct SV* * p_array;
    int i_0;
    int i_n;
    int size;
};

struct strpool {
    int i_str;
    int i_pool;
    int n_str;
    int n_pool;
    int* pn_str;
    unsigned char* pc_pool;
};

struct strhash {
    int n_size;
    int n_count;
    int n_val_size;
    char * p_exist;
    int * p_key;
    struct strpool pool;
    void * p_val;
};

struct HV {
    int n_size;
    int n_count;
    int n_val_size;
    char * p_exist;
    int * p_key;
    struct strpool pool;
    struct SV* * p_val;
};

struct STRING {
    char* s;
    int n;
    int size;
    int pos;
};

struct GOTO {
    struct CV* cv;
    int i;
};

struct SV {
    unsigned char type;
    unsigned char flag;
    unsigned char copy;
    unsigned char refcnt;
    union {
        struct STRING S;
        void* p;
        int n;
        struct GOTO G;
        double f;
    } value;
};

struct OP {
    int type;
    union {
        struct CV* cv;
        struct SV* sv;
        int n;
        struct OP* op;
    } left;
    union {
        struct CV* cv;
        struct SV* sv;
        int n;
        struct OP* op;
    } right;
};

struct stash {
    int n_size;
    int n_count;
    int n_val_size;
    char * p_exist;
    int * p_key;
    struct strpool pool;
    int* p_val;
};

struct call_stack_entry {
    struct SV* sv_local;
    int n;
    int n_size;
};

struct CV {
    struct stash* stash;
    int i_file;
    int i_start;
    int n_vars;
    int n_seq;
    struct OP* op_block;
    int flag;
    char debug;
};

struct T {
    int a1;
    int a2;
    void* a3;
};

union VAL {
    struct CV* cv;
    int n;
    struct OP* op;
    char* s;
};

struct TOK {
    int type;
    union VAL value;
};

struct buf_chain {
    char s[1024];
    int n;
    struct buf_chain * next;
};

struct stash* stash_new();
int f_stash_get(struct stash* stash, char* s, int n);
void * f_darray_expand(void * P, int n_rec_size, int* pn_size);
void f_resize_strpool_n(struct strpool* p_strpool, int n_size);
int f_addto_strpool(struct strpool* p_strpool, char* s, int n);
void f_free_strpool(struct strpool* p_strpool);
int f_strhash_lookup(void* hash, unsigned char* pc_key, int keylen);
struct SV* get_sv(int tn_type);
struct SV* sv_from_s(char* s, int n);
int f_strhash_lookup_left(void* hash, unsigned char* pc_key, int keylen);
struct AV* AV_new();
void AV_push(struct AV* av, struct SV* sv_value);
void run_repl();
void SV_resize(struct SV* sv, int n);
void f_strhash_resize(void * hash, int n_size);
void AV_resize(struct AV* av, int n);
void SV_refinc(struct SV* sv);
int perl_parse(char* s_in, FILE* file_in, struct TOK* stack, int i_top);
struct SV* eval_op(struct OP* op, int tn_context, int tn_level);
void* do_string(struct SV* sv);
void SV_refdec(struct SV* sv);
char* f_skip_spaces(char* s);
char* f_get_regex(char* s, struct OP ** p_op);
struct OP* get_op();
char* f_get_number(char* s, struct SV* sv);
char* f_get_str_q(char* s, struct OP ** p_op);
char* f_get_str_qq(char* s, struct OP ** p_op);
void dump_parse_stack(struct TOK* stack, int i_top, struct TOK cur, char* s);
char* f_scan_word(char* s);
char* f_scan_id(char* s);
int my_word(char* s, int n);
char* f_skip_simple_spaces(char* s);
int keyword_op(char* s);
char* f_scan_delim(char* s, char** p_str, int* pn_len);
void CV_begin();
void SV_append_s(struct SV* sv, char* s, int n);
int find_global(char* s_name);
int find_local(char* s_name);
struct OP* f_parse_var_special(char char_sigil, char* s);
char* f_scan_operator(char* s, int* p_id);
char* get_OP_name(int n_OP);
struct OP* f_new_op(int tn_type, struct OP* op_a, struct OP* op_b);
struct CV* CV_close(struct OP* op_block);
void f_flatten_op_list(struct OP* op, int tn_type);
struct OP* get_op_list(int n);
struct SV* run_cv(struct CV* cv, int tn_context, int tn_level);
struct SV* SV_copy(struct SV* sv_ret, struct SV* sv);
struct SV* eval_list(struct OP* op_a, struct OP* op_b, int tn_context, int tn_level);
struct SV* get_svreg(int tn_type);
int do_bool(struct SV* sv);
void SV_to_int(struct SV* sv);
struct SV* AV_get(struct AV* av, int i);
struct SV * AV_shift(struct AV* av);
void do_print(struct SV* sv_io, struct AV* av);
void do_printf(struct SV* sv_io, struct AV* av);
char * get_WORD_name(int id);
struct SV* HV_get(struct HV* hv, char* s_key, int len);
void HV_set(struct HV* hv, char* s_key, int len, struct SV* sv_value);
int do_int(struct SV* sv);
void AV_set(struct AV* av, int i, struct SV* sv_value);
void do_assign(struct SV* sv_var, struct SV* sv_val);
void SV_undef(struct SV* sv);
void AV_free(struct AV* av);
void SV_append_sv(struct SV* sv, struct SV* sv_b);
float do_float(struct SV* sv);
void SV_string_on_write(struct SV* sv);
void SV_to_string(struct SV* sv);
void SV_to_float(struct SV* sv);
void SV_append_i(struct SV* sv, int i);
void SV_append_f(struct SV* sv, double f);
char* get_SV_name(int n_type);
void HV_free(struct HV* hv);
char* f_load_src(char* s);
char* f_skip_line(char* s);
struct OP* f_parse_str_qq(char* s, bool is_regex);
char* f_get_v_string(char* s, struct SV* sv);
char * get_T_name(int n_type);
char* f_scan_delim_quick(char* s);
struct CV* CV_new();
int f_op_iter_count(struct OP* op, int tn_type);
struct OP* f_op_iter_get(struct OP* op, int tn_type, struct OP* op_list);
int get_copy();
int sv_string_int(struct SV* sv);
struct SV* SV_fmt(struct SV* sv, char char_fmt, int n_width, int n_prec, int n_flag);
void AV_unshift(struct AV* av, int n);
void AV_grow(struct AV* av, int n);
struct HV* HV_new();
double sv_string_float(struct SV* sv);
int hex(char* s, int n);
int utf(char* s, unsigned int code);
struct OP* f_parse_var(char* s, int n);
struct OP* f_parse_var_simple(char* s, int n);

struct TOK parse_stack[100];
int i_stack_top;
char* SV_names[] = {"SVt_undef","SVt_int","SVt_float","SVt_BASIC","SVt_av","SVt_hv","SVt_sv","SVt_string","SVt_cv","SVt_goto","SVt_io","SVt_regex"};
char* OP_names[] = {
    "OP_SEQ",
    "OP_LIST",
    "OP_CONST",
    "OP_CV",
    "OP_block",
    "OP_GOTO_LABEL",
    "OP_GOTO",
    "OP_BREAK",
    "OP_RETURN",
    "OP_REQUIRE",
    "OP_Plus",
    "OP_Minus",
    "OP_Mult",
    "OP_Div",
    "OP_MultMult",
    "OP_Mod",
    "OP_Or",
    "OP_And",
    "OP_Ctrl",
    "OP_GtGt",
    "OP_LtLt",
    "OP_Dot",
    "OP_x",
    "OP_EqEq",
    "OP_EmarkEq",
    "OP_Lt",
    "OP_Gt",
    "OP_LtEq",
    "OP_GtEq",
    "OP_LtEqGt",
    "OP_eq",
    "OP_ne",
    "OP_lt",
    "OP_gt",
    "OP_le",
    "OP_ge",
    "OP_cmp",
    "OP_PlusEq",
    "OP_MinusEq",
    "OP_MultEq",
    "OP_DivEq",
    "OP_ModEq",
    "OP_OrEq",
    "OP_AndEq",
    "OP_CtrlEq",
    "OP_GtGtEq",
    "OP_LtLtEq",
    "OP_DotEq",
    "OP_or",
    "OP_and",
    "OP_UMINUS",
    "OP_NOT",
    "OP_GLOBAL",
    "OP_LOCAL",
    "OP_MY",
    "OP_ASSIGN",
    "OP_SUB",
    "OP_Fcall",
    "OP_IF",
    "OP_ELIF",
    "OP_ELSE",
    "OP_IF_YES",
    "OP_IF_NO",
    "OP_while",
    "OP_for",
    "OP_join",
    "OP_Re",
    "OP_ReC",
    "OP_ReMatch",
    "OP_ReReplace",
    "OP_VarMatch",
    "OP_UNARY",
    "OP_INC",
    "OP_DEC",
    "OP_FN_LIST",
    "OP_FN_1",
    "OP_SIGIL",
    "OP_ARRAY_INDEX",
    "OP_HASH_INDEX",
};
struct stash* stash_local = NULL;
struct stash* stash_global = NULL;
struct stash * * g_stashes = NULL;
int g_stashes_len = 0;
int g_stashes_size = 0;
struct SV * g_global = NULL;
int g_global_len = 0;
int g_global_size = 0;
struct call_stack_entry * g_file_scopes = NULL;
int g_file_scopes_len = 0;
int g_file_scopes_size = 0;
int cur_file_scope = 0;
struct SV * g_local = NULL;
int g_local_len = 0;
int g_local_size = 0;
struct strpool local_names;
int * local_vars = NULL;
int local_vars_len = 0;
int local_vars_size = 0;
struct CV* * lex_stack = NULL;
int lex_stack_len = 0;
int lex_stack_size = 0;
struct CV* cv_cur = NULL;
int i_seq = 0;
struct SV svregs[100];
int i_svreg = 0;
int n_svreg = 0;
struct T * heap = NULL;
int heap_len = 0;
int heap_size = 0;
struct OP* op_freelist = NULL;
int i_op_free;
int n_op_free;
struct SV* sv_freelist = NULL;
int i_sv_free;
int n_sv_free;
unsigned svcopy[100];
int i_svcopy = 1;
int n_svcopy = 1;
char s_filename_buf[1024];
char* s_regex_str;
int n_regex_len;
int regex_offs[30];
int n_regex_caps;
int n_debug = 0;
char* T_op_names[] = {
    "T_BOC",
    "T_BOS",
    "T_EOC",
    "T_EOF",
    "T_Semi",
    "T_or",
    "T_and",
    "T_not",
    "T_FN_LIST",
    "T_FN_GOTO",
    "T_Comma",
    "T_Eq",
    "T_PlusEq",
    "T_MinusEq",
    "T_MultEq",
    "T_DivEq",
    "T_ModEq",
    "T_DotEq",
    "T_OrEq",
    "T_AndEq",
    "T_CtrlEq",
    "T_GtGtEq",
    "T_LtLtEq",
    "T_Colon",
    "T_Qmark",
    "T_DotDot",
    "T_OrOr",
    "T_AndAnd",
    "T_Or",
    "T_Ctrl",
    "T_And",
    "T_EqEq",
    "T_EmarkEq",
    "T_LtEqGt",
    "T_eq",
    "T_ne",
    "T_cmp",
    "T_Lt",
    "T_Gt",
    "T_LtEq",
    "T_GtEq",
    "T_lt",
    "T_gt",
    "T_le",
    "T_ge",
    "T_FN_1",
    "T_GtGt",
    "T_LtLt",
    "T_Plus",
    "T_Minus",
    "T_Dot",
    "T_Mult",
    "T_Div",
    "T_Mod",
    "T_x",
    "T_EqTlide",
    "T_UMINUS",
    "T_Tlide",
    "T_Emark",
    "T_UAMPER",
    "T_MultMult",
    "T_PlusPlus",
    "T_MinusMinus",
    "T_MinusGt",
    "T_UNARY",
    "T_SIGIL",
    "T_MY",
    NULL
};
char* WORD_names[] = {
    "eq",
    "ne",
    "le",
    "ge",
    "lt",
    "gt",
    "cmp",
    "or",
    "and",
    "not",
    "x",
    "OPERATOR",
    "goto",
    "next",
    "last",
    "redo",
    "return",
    "FN_GOTO",
    "print",
    "printf",
    "warn",
    "die",
    "join",
    "open",
    "FN_LIST",
    "uc",
    "lc",
    "ucfirst",
    "lcfirst",
    "quotemeta",
    "close",
    "fread",
    "FN_1",
    "use",
    "require",
    "no",
    "package",
    "sub",
    "if",
    "elsif",
    "else",
    "while",
    "for",
    "my",
    "our",
    "local",
    NULL
};
struct SV* sv_TRUE;
struct SV* sv_FALSE;
struct SV* sv_EMPTY;
int I_LIST_SEPARATOR;
int I_at_INC;
int I_at_ARG;
int I_OFS;
int I_STDIN;
int I_STDOUT;
int I_STDERR;
int I_ARG;
int I_PREMATCH;
int I_POSTMATCH;
int I_MATCH;
int I_1;
int I_2;
int I_3;
int I_4;
int I_5;
int I_6;
int I_7;
int I_8;
int I_9;
char* * modules = NULL;
int modules_len = 0;
int modules_size = 0;
struct CV* * subs = NULL;
int subs_len = 0;
int subs_size = 0;
FILE* file_src;
char* s_src_end;
char s_line_buffer[10000];
char s_src_buffer[1024+1];
int n_src_extra = 0;

struct stash* stash_new(){
    struct stash* stash;

    stash=(struct stash*)calloc(1, sizeof(struct stash));
    stash->n_val_size = sizeof(int);
    return stash;
}

int f_stash_get(struct stash* stash, char* s, int n){
    int k;

    if(stash->n_size == 0){
        return 0;
    }
    k = f_strhash_lookup(stash, (unsigned char*)s, n);
    if(stash->p_exist[k]){
        return stash->p_val[k];
    }
    else{
        return 0;
    }
}

void * f_darray_expand(void * P, int n_rec_size, int* pn_size){
    int tn_temp;

    tn_temp = (*pn_size) * 2 / 3;
    if(tn_temp < 64){
        tn_temp = 64;
    }
    (*pn_size) += tn_temp;
    P = realloc(P, (*pn_size) * n_rec_size);
    return P;
}

void f_resize_strpool_n(struct strpool* p_strpool, int n_size){
    int tn_avg_str_size;

    tn_avg_str_size = 6;
    if(p_strpool->i_str > 0){
        tn_avg_str_size = p_strpool->i_pool / p_strpool->i_str + 1;
    }
    p_strpool->n_str = n_size;
    p_strpool->n_pool = tn_avg_str_size * p_strpool->n_str;
    p_strpool->pn_str = realloc(p_strpool->pn_str, p_strpool->n_str * sizeof(int));
    p_strpool->pc_pool = realloc(p_strpool->pc_pool, p_strpool->n_pool);
    p_strpool->pc_pool[p_strpool->n_pool-1] = 0;
    if(p_strpool->i_str == 0){
        p_strpool->pn_str[0] = 0;
    }
}

int f_addto_strpool(struct strpool* p_strpool, char* s, int n){
    int n_size;
    int tn_avg_str_size;

    if(p_strpool->i_str + 2 >= p_strpool->n_str){
        n_size = p_strpool->i_str * 3 / 2 + 10;
        f_resize_strpool_n(p_strpool, n_size);
    }
    if(p_strpool->i_pool + n >= p_strpool->n_pool){
        tn_avg_str_size = 6;
        if(p_strpool->i_str > 0){
            tn_avg_str_size = p_strpool->i_pool / p_strpool->i_str + 1;
        }
        p_strpool->n_pool = tn_avg_str_size * p_strpool->n_str + n;
        p_strpool->pc_pool = realloc(p_strpool->pc_pool, p_strpool->n_pool);
    }
    memcpy(p_strpool->pc_pool + p_strpool->i_pool, s, n);
    p_strpool->i_str++;
    p_strpool->i_pool += n;
    p_strpool->pc_pool[p_strpool->i_pool] = '\0';
    p_strpool->i_pool += 1;
    p_strpool->pn_str[p_strpool->i_str] = p_strpool->i_pool;
    return p_strpool->i_str - 1;
}

void f_free_strpool(struct strpool* p_strpool){
    free(p_strpool->pn_str);
    free(p_strpool->pc_pool);
    memset(p_strpool, 0, sizeof(struct strpool));
}

int main(int argc, char** argv){
    struct SV* sv;
    int k;
    struct AV* av;

    stash_global = stash_new();
    if(g_stashes_len + 1 > g_stashes_size){
        g_stashes = f_darray_expand(g_stashes, sizeof(struct stash*), &g_stashes_size);
    }
    g_stashes[g_stashes_len] = stash_global;
    g_stashes_len++;
    if(g_global_len + 1 > g_global_size){
        g_global_size = (g_global_len + 1) * 5 / 3 + 10;
        g_global=(struct SV*)realloc(g_global, g_global_size*sizeof(struct SV));
    }
    memset(g_global + g_global_len, 0, (1) * sizeof(*g_global));
    g_global_len++;
    svcopy[0] = 1;
    sv_TRUE = get_sv(0);
    sv_TRUE->refcnt = -1;
    sv_FALSE = get_sv(0);
    sv_FALSE->refcnt = -1;
    sv_TRUE->type = SVt_int;
    sv_TRUE->value.n = 1;
    sv_FALSE->type = SVt_int;
    sv_FALSE->value.n = 0;
    sv_EMPTY = sv_from_s("", 0);
    sv_EMPTY->refcnt = -1;
    if(g_global_len + 100 > g_global_size){
        g_global_size = (g_global_len + 100) * 5 / 3 + 10;
        g_global=(struct SV*)realloc(g_global, g_global_size*sizeof(struct SV));
    }
    memset(g_global + g_global_len, 0, (100) * sizeof(*g_global));
    g_global_len = 1;
    I_LIST_SEPARATOR = g_global_len++;
    sv = &g_global[I_LIST_SEPARATOR];
    k = f_strhash_lookup_left(stash_global, (unsigned char*)"$LIST_SEPARATOR", 15);
    stash_global->p_val[k] = I_LIST_SEPARATOR;
    sv->type = SVt_undef;
    sv->type = SVt_string;
    sv->value.S.s = " ";
    sv->value.S.n = strlen(" ");
    sv->value.S.size = 0;
    I_at_INC = g_global_len++;
    sv = &g_global[I_at_INC];
    k = f_strhash_lookup_left(stash_global, (unsigned char*)"@INC", 4);
    stash_global->p_val[k] = I_at_INC;
    av = AV_new();
    sv->type = SVt_av;
    sv->value.p = av;
    sv = sv_from_s(".", 0);
    AV_push(av, sv);
    I_at_ARG = g_global_len++;
    sv = &g_global[I_at_ARG];
    k = f_strhash_lookup_left(stash_global, (unsigned char*)"@ARG", 4);
    stash_global->p_val[k] = I_at_ARG;
    av = AV_new();
    sv->type = SVt_av;
    sv->value.p = av;
    I_OFS = g_global_len++;
    sv = &g_global[I_OFS];
    k = f_strhash_lookup_left(stash_global, (unsigned char*)"$OFS", 4);
    stash_global->p_val[k] = I_OFS;
    sv->type = SVt_undef;
    I_STDIN = g_global_len++;
    sv = &g_global[I_STDIN];
    k = f_strhash_lookup_left(stash_global, (unsigned char*)"*STDIN", 6);
    stash_global->p_val[k] = I_STDIN;
    sv->type = SVt_io;
    I_STDOUT = g_global_len++;
    sv = &g_global[I_STDOUT];
    k = f_strhash_lookup_left(stash_global, (unsigned char*)"*STDOUT", 7);
    stash_global->p_val[k] = I_STDOUT;
    sv->type = SVt_io;
    I_STDERR = g_global_len++;
    sv = &g_global[I_STDERR];
    k = f_strhash_lookup_left(stash_global, (unsigned char*)"*STDERR", 7);
    stash_global->p_val[k] = I_STDERR;
    sv->type = SVt_io;
    g_global[I_STDIN].value.p = stdin;
    g_global[I_STDOUT].value.p = stdout;
    g_global[I_STDERR].value.p = stderr;
    I_ARG = g_global_len++;
    sv = &g_global[I_ARG];
    k = f_strhash_lookup_left(stash_global, (unsigned char*)"$ARG", 4);
    stash_global->p_val[k] = I_ARG;
    sv->type = SVt_undef;
    I_PREMATCH = g_global_len++;
    sv = &g_global[I_PREMATCH];
    k = f_strhash_lookup_left(stash_global, (unsigned char*)"$PREMATCH", 9);
    stash_global->p_val[k] = I_PREMATCH;
    sv->type = SVt_undef;
    I_POSTMATCH = g_global_len++;
    sv = &g_global[I_POSTMATCH];
    k = f_strhash_lookup_left(stash_global, (unsigned char*)"$POSTMATCH", 10);
    stash_global->p_val[k] = I_POSTMATCH;
    sv->type = SVt_undef;
    I_MATCH = g_global_len++;
    sv = &g_global[I_MATCH];
    k = f_strhash_lookup_left(stash_global, (unsigned char*)"$MATCH", 6);
    stash_global->p_val[k] = I_MATCH;
    sv->type = SVt_undef;
    I_1 = g_global_len++;
    sv = &g_global[I_1];
    k = f_strhash_lookup_left(stash_global, (unsigned char*)"$1", 2);
    stash_global->p_val[k] = I_1;
    sv->type = SVt_undef;
    I_2 = g_global_len++;
    sv = &g_global[I_2];
    k = f_strhash_lookup_left(stash_global, (unsigned char*)"$2", 2);
    stash_global->p_val[k] = I_2;
    sv->type = SVt_undef;
    I_3 = g_global_len++;
    sv = &g_global[I_3];
    k = f_strhash_lookup_left(stash_global, (unsigned char*)"$3", 2);
    stash_global->p_val[k] = I_3;
    sv->type = SVt_undef;
    I_4 = g_global_len++;
    sv = &g_global[I_4];
    k = f_strhash_lookup_left(stash_global, (unsigned char*)"$4", 2);
    stash_global->p_val[k] = I_4;
    sv->type = SVt_undef;
    I_5 = g_global_len++;
    sv = &g_global[I_5];
    k = f_strhash_lookup_left(stash_global, (unsigned char*)"$5", 2);
    stash_global->p_val[k] = I_5;
    sv->type = SVt_undef;
    I_6 = g_global_len++;
    sv = &g_global[I_6];
    k = f_strhash_lookup_left(stash_global, (unsigned char*)"$6", 2);
    stash_global->p_val[k] = I_6;
    sv->type = SVt_undef;
    I_7 = g_global_len++;
    sv = &g_global[I_7];
    k = f_strhash_lookup_left(stash_global, (unsigned char*)"$7", 2);
    stash_global->p_val[k] = I_7;
    sv->type = SVt_undef;
    I_8 = g_global_len++;
    sv = &g_global[I_8];
    k = f_strhash_lookup_left(stash_global, (unsigned char*)"$8", 2);
    stash_global->p_val[k] = I_8;
    sv->type = SVt_undef;
    I_9 = g_global_len++;
    sv = &g_global[I_9];
    k = f_strhash_lookup_left(stash_global, (unsigned char*)"$9", 2);
    stash_global->p_val[k] = I_9;
    sv->type = SVt_undef;
    if(subs_len + 10 > subs_size){
        subs_size = (subs_len + 10) * 5 / 3 + 10;
        subs=(struct CV**)realloc(subs, subs_size*sizeof(struct CV*));
    }
    memset(subs + subs_len, 0, (10) * sizeof(*subs));
    subs_len = 1;
    run_repl();
    return 0;
}

int f_strhash_lookup(void* hash, unsigned char* pc_key, int keylen){
    struct strhash * h = hash;
    unsigned int tu_h;
    int i;
    int k;
    struct strpool* p_strpool;

    if(keylen == 0){
        keylen = strlen((char*)pc_key);
    }
    if(h->n_size == 0){
        return 0;
    }
    tu_h = 2166136261u;
    for(i=0; i<keylen; i++){
        tu_h = tu_h ^ pc_key[i];
        tu_h = tu_h * 16777619;
    }
    k = (int)(tu_h % h->n_size);
    p_strpool = &h->pool;
    while(1){
        if(!h->p_exist[k]){
            return k;
        }
        else{
            if((p_strpool->pn_str[h->p_key[k]+1] - p_strpool->pn_str[h->p_key[k]] - 1) == keylen && memcmp((p_strpool->pc_pool + p_strpool->pn_str[h->p_key[k]]), pc_key, keylen) == 0){
                return k;
            }
        }
        if(k == 0){
            k = h->n_size - 1;
        }
        else{
            k--;
        }
    }
}

struct SV* get_sv(int tn_type){
    struct SV* sv;

    if(i_sv_free >= n_sv_free){
        sv_freelist=(struct SV*)calloc(100, sizeof(struct SV));
        if(heap_len + 1 > heap_size){
            heap = f_darray_expand(heap, sizeof(struct T), &heap_size);
        }
        heap[heap_len].a1 = HEAP_sv;
        heap[heap_len].a2 = 100;
        heap[heap_len].a3 = sv_freelist;
        heap_len++;
        i_sv_free = 0;
        n_sv_free = 100;
    }
    sv = &sv_freelist[i_sv_free++];
    sv->type = tn_type;
    sv->refcnt = 1;
    return sv;
}

struct SV* sv_from_s(char* s, int n){
    struct SV* sv;

    if(n == 0){
        n = strlen(s);
    }
    sv = get_sv(SVt_string);
    SV_resize(sv, n);
    memcpy(sv->value.S.s, s, n);
    sv->value.S.n = n;
    return sv;
}

int f_strhash_lookup_left(void* hash, unsigned char* pc_key, int keylen){
    struct strhash * h = hash;
    int k;

    if(keylen == 0){
        keylen = strlen((char*)pc_key);
    }
    if(h->n_size == 0 || h->n_count + 1 >= h->n_size || (h->n_size > 20 && h->n_count >= h->n_size * 85 / 100)){
        f_strhash_resize(h, 0);
    }
    k = f_strhash_lookup(h, pc_key, keylen);
    if(!h->p_exist[k]){
        h->p_key[k] = f_addto_strpool(&h->pool, (char*)pc_key, keylen);
        h->p_exist[k] = 1;
        h->n_count++;
    }
    return k;
}

struct AV* AV_new(){
    struct AV* av;

    av=(struct AV*)calloc(1, sizeof(struct AV));
    return av;
}

void AV_push(struct AV* av, struct SV* sv_value){
    if(av->i_n + 1 >= av->size){
        AV_resize(av, 0);
    }
    av->p_array[av->i_n] = sv_value;
    av->i_n++;
    if(sv_value){
        SV_refinc(sv_value);
    }
}

void run_repl(){
    char* s;
    struct SV* sv_ret;
    struct SV* sv_str;

    i_stack_top = 0;
    puts("");
    puts("type \"quit\" to exit.");
    puts("");
    while(1){
        s = readline("> ");
        if(!s || strcmp(s, "quit") == 0){
            return;
        }
        add_history(s);
        i_stack_top = perl_parse(s, NULL, parse_stack, i_stack_top);
        if(i_stack_top == 1 && parse_stack[i_stack_top-1].type == T_ATOM){
            sv_ret = eval_op(parse_stack[i_stack_top-1].value.op, 0, 0);
            sv_str = do_string(sv_ret);
            if(sv_ret && sv_str){
                sv_str->value.S.s[sv_str->value.S.n] = '\0';
                printf("  %s\n", sv_str->value.S.s);
            }
            if(sv_ret && (sv_ret->flag & 3) == SVf_register){
                SV_refdec(sv_ret);
                sv_ret->flag = 0;
                n_svreg--;
            }
            if(sv_str && (sv_str->flag & 3) == SVf_register){
                SV_refdec(sv_str);
                sv_str->flag = 0;
                n_svreg--;
            }
            i_stack_top = 0;
        }
        else{
            puts("[cont]");
        }
    }
}

void SV_resize(struct SV* sv, int n){
    if(!(sv->type == SVt_string)){
        puts("assert error: ! (sv->type==SVt_string)");
        exit(0);
    }
    if(n == 0){
        n = sv->value.S.size * 5 / 3 + 20;
    }
    else{
        n += 1;
    }
    if(n > sv->value.S.size){
        sv->value.S.s = realloc(sv->value.S.s, n);
        sv->value.S.size = n;
    }
}

void f_strhash_resize(void * hash, int n_size){
    struct strhash * h = hash;
    char * tp_exist = h->p_exist;
    int * tp_key = h->p_key;
    void * tp_val = h->p_val;
    int tn_old_size;
    struct strpool* p_strpool;
    int k;

    if(n_size == 0){
        if(h->n_size <= 0){
            n_size = 10;
        }
        else{
            n_size = h->n_size * 5 / 3;
        }
    }
    else if(n_size <= h->n_size){
        return;
    }
    tn_old_size = h->n_size;
    h->n_size = n_size;
    h->p_key=(int*)calloc(n_size, sizeof(int));
    h->p_exist=(char*)calloc(n_size, sizeof(char));
    h->p_val=(void*)calloc((n_size*h->n_val_size), sizeof(void));
    f_resize_strpool_n(&h->pool, n_size);
    p_strpool = &h->pool;
    if(tn_old_size > 0){
        int i;
        for(i=0; i<tn_old_size; i++){
            if(tp_exist[i]){
                k = f_strhash_lookup(h, (p_strpool->pc_pool + p_strpool->pn_str[tp_key[i]]), (p_strpool->pn_str[tp_key[i]+1] - p_strpool->pn_str[tp_key[i]] - 1));
                h->p_exist[k] = 1;
                h->p_key[k] = tp_key[i];
                memcpy(h->p_val + k * h->n_val_size, tp_val + i * h->n_val_size, h->n_val_size);
            }
        }
        free(tp_exist);
        free(tp_key);
        free(tp_val);
    }
}

void AV_resize(struct AV* av, int n){
    bool tb_neg = 0;

    if(n == 0){
        n = (av->i_n - av->i_0) * 5 / 3 + 10 * 2;
    }
    else if(n < 0){
        tb_neg = 1;
        n = -n;
    }
    if(av->size == 0){
        av->p_array=(struct SV**)malloc(n*sizeof(struct SV*));
        av->i_0 = 10;
        av->i_n = 10;
        av->size = n;
    }
    else if(n < av->size){
        if(av->i_0 > 10){
            struct SV** p_sv_1;
            struct SV** p_sv_2;
            struct SV** p_sv_n;
            if(tb_neg){
                p_sv_1 = av->p_array + n - 10 - 1;
                p_sv_2 = av->p_array + av->i_n - 1;
                p_sv_n = av->p_array + av->i_0;
                while(p_sv_2 >= p_sv_n){
                    *p_sv_1-- = *p_sv_2--;
                }
                av->i_0 = (int)(p_sv_1 - av->p_array + 1);
                av->i_n = n - 10;
            }
            else{
                p_sv_1 = av->p_array + 10;
                p_sv_2 = av->p_array + av->i_0;
                p_sv_n = av->p_array + av->i_n;
                while(p_sv_2 < p_sv_n){
                    *p_sv_1++ = *p_sv_2++;
                }
                av->i_0 = 10;
                av->i_n = (int)(p_sv_1 - av->p_array);
            }
        }
    }
    else{
        struct SV** p_sv;
        struct SV** p_sv_1;
        struct SV** p_sv_2;
        struct SV** p_sv_n;
        p_sv=(struct SV**)malloc(n*sizeof(struct SV*));
        if(tb_neg){
            p_sv_1 = p_sv + n - 10 - 1;
            p_sv_2 = av->p_array + av->i_n - 1;
            p_sv_n = av->p_array + av->i_0;
            while(p_sv_2 >= p_sv_n){
                *p_sv_1-- = *p_sv_2--;
            }
            av->i_0 = (int)(p_sv_1 - p_sv + 1);
            av->i_n = n - 10;
        }
        else{
            p_sv_1 = p_sv + 10;
            p_sv_2 = av->p_array + av->i_0;
            p_sv_n = av->p_array + av->i_n;
            while(p_sv_2 < p_sv_n){
                *p_sv_1++ = *p_sv_2++;
            }
            av->i_0 = 10;
            av->i_n = (int)(p_sv_1 - p_sv);
        }
        free(av->p_array);
        av->p_array = p_sv;
        av->size = n;
    }
}

void SV_refinc(struct SV* sv){
    sv->refcnt++;
}

int perl_parse(char* s_in, FILE* file_in, struct TOK* stack, int i_top){
    char* s;
    struct TOK cur = {0,0};
    struct OP* op_var;
    struct OP* op;
    struct SV* sv;
    char* s2;
    bool has_package;
    int n;
    int tn_word;
    int tn_op;
    int k;
    struct AV* av;
    char char_save;
    bool tb_exist;
    char* s3;
    int n_in_my;
    int tn_bos_op;
    int tn_unary_word;
    int tn_op_type;
    int i_var;
    struct SV* sv_var;
    char char_sigil;
    char ts_var_buf[256];
    int i_str;
    struct strpool* p_strpool;
    struct OP* op_fh;
    struct OP* op_fread;
    struct CV* cv;
    int i;
    int tn_i;
    struct OP* op_b;
    int tn_type;
    char char_index;
    struct OP* op_index;
    struct OP* op_v;
    struct SV* sv_name;
    struct OP* op_tmp;
    struct OP* op_goto;
    struct OP* op_break;
    struct OP* op_cond;
    struct OP* op_list;
    struct OP* op_cv;
    struct OP* op_init;
    struct OP* op_cont;
    bool tb_cv;

    file_src = file_in;
    if(s_in){
        s_src_end = s_in + strlen(s_in);
    }
    s = s_in;
    if(i_top == 0){
        stack[0].type = T_BOC;
        stack[0].value.n = 0;
        i_top = 1;
    }
    while(1){
        lexer:
        s = f_skip_spaces(s);
        if(s == NULL){
            cur.type = T_EOF;
            cur.value.n = 0;
            goto try_reduce;
        }
        else if(*s == '/' && (stack[i_top-1].type & 0xffff00)){
            struct OP* op_re;
            s = f_get_regex(s, &op_re);
            op_var = get_op();
            op_var->type = OP_GLOBAL;
            op_var->right.op = NULL;
            op_var->right.n = I_ARG;
            op = get_op();
            op->type = OP_ReMatch;
            op->left.op = op_var;
            op->right.op = op_re;
            cur.type = T_ATOM;
            cur.value.op = op;
            goto do_shift;
        }
        else if(isdigit(*s)){
            sv = get_sv(0);
            s = f_get_number(s, sv);
            cur.type = T_ATOM;
            cur.value.op = get_op();
            cur.value.op->type = OP_CONST;
            cur.value.op->right.op = NULL;
            cur.value.op->right.sv = sv;
            goto do_shift;
        }
        else if((*s=='\'' || *s=='"')){
            struct OP* op;
            if(*s == '\''){
                s = f_get_str_q(s, &op);
            }
            else{
                s = f_get_str_qq(s, &op);
            }
            if(s == NULL){
                puts("unterminated string");
                dump_parse_stack(stack, i_top, cur, s);
                exit(0);
            }
            cur.type = T_ATOM;
            cur.value.op = op;
            goto do_shift;
        }
        else if(isword(*s) || (s[0] == ':' && s[1] == ':')){
            s2 = s;
            s = f_scan_word(s);
            has_package = 0;
            if(s[0] == ':' && s[1] == ':'){
                s = f_scan_id(s + 2);
                has_package = 1;
            }
            n = (int)(s - s2);
            if(!has_package && stack[i_top-1].type != T_SIGIL){
                tn_word = my_word(s2, n);
                if(tn_word){
                    s = f_skip_simple_spaces(s);
                    if(!s){
                        s = s_src_end;
                    }
                    if(tn_word < WORD_OPERATOR){
                        tn_op = keyword_op(s2);
                        cur.type = tn_op;
                        cur.value.n = 0;
                        goto try_reduce;
                    }
                    else if(tn_word < WORD_FN_GOTO){
                        cur.type = T_FN_GOTO;
                        cur.value.n = tn_word;
                        goto try_reduce;
                    }
                    else if(tn_word < WORD_FN_LIST){
                        if(*s == '('){
                            op = get_op();
                            op->type = OP_FN_LIST;
                            op->left.n = tn_word;
                            op->right.n = 0;
                            cur.type = T_UNARY;
                            cur.value.op = op;
                        }
                        else{
                            cur.type = T_FN_LIST;
                            cur.value.n = tn_word;
                        }
                        goto try_reduce;
                    }
                    else if(tn_word < WORD_FN_1){
                        if(*s == '('){
                            op = get_op();
                            op->type = OP_FN_1;
                            op->left.n = tn_word;
                            op->right.n = 0;
                            cur.type = T_UNARY;
                            cur.value.op = op;
                        }
                        else{
                            cur.type = T_FN_1;
                            cur.value.n = tn_word;
                        }
                        goto try_reduce;
                    }
                    else if(tn_word == WORD_package){
                        s = f_skip_simple_spaces(s);
                        if(!s){
                            s = s_src_end;
                        }
                        if(isword1st(*s)){
                            s2 = s;
                            s = f_scan_word(s);
                            has_package = 0;
                            if(s[0] == ':' && s[1] == ':'){
                                s = f_scan_id(s + 2);
                                has_package = 1;
                            }
                            n = (int)(s - s2);
                            if(n + 2 < 1024){
                                memcpy(s_filename_buf, s2, n);
                                strcpy(s_filename_buf + n, "::");
                                stash_global = stash_new();
                                if(g_stashes_len + 1 > g_stashes_size){
                                    g_stashes = f_darray_expand(g_stashes, sizeof(struct stash*), &g_stashes_size);
                                }
                                g_stashes[g_stashes_len] = stash_global;
                                g_stashes_len++;
                                k = f_strhash_lookup_left(g_stashes[0], (unsigned char*)s_filename_buf, strlen(s_filename_buf));
                                g_stashes[0]->p_val[k] = g_stashes_len - 1;
                                s = f_skip_simple_spaces(s);
                                if(!s){
                                    s = s_src_end;
                                }
                                if(*s == ';'){
                                    s++;
                                }
                                else{
                                    puts("semicolon expected after 'use'");
                                    dump_parse_stack(stack, i_top, cur, s);
                                    exit(0);
                                }
                                goto lexer;
                            }
                            else{
                                puts("name too long");
                                dump_parse_stack(stack, i_top, cur, s);
                                exit(0);
                            }
                        }
                        else{
                            puts("package");
                            dump_parse_stack(stack, i_top, cur, s);
                            exit(0);
                        }
                    }
                    else if(tn_word == WORD_use || tn_word == WORD_no){
                        s = f_skip_simple_spaces(s);
                        if(!s){
                            s = s_src_end;
                        }
                        if(isdigit(s[0]) || (s[0] == 'v' && isdigit(s[1]))){
                            s2 = s;
                            if(*s == 'v'){
                                s++;
                            }
                            while(isdigit(*s) || *s == '.'){
                                s++;
                            }
                        }
                        else if(isword1st(s[0])){
                            int i;
                            s2 = s;
                            s = f_scan_word(s);
                            has_package = 0;
                            if(s[0] == ':' && s[1] == ':'){
                                s = f_scan_id(s + 2);
                                has_package = 1;
                            }
                            n = (int)(s - s2);
                            if(n==3 && strncmp(s2, "lib", 3)==0){
                                s = f_skip_simple_spaces(s);
                                if(!s){
                                    s = s_src_end;
                                }
                                if((*s=='\'' || *s=='"')){
                                    char* s2;
                                    int n;
                                    s = f_scan_delim(s, &s2, &n);
                                    s2[n] = '\0';
                                    sv = sv_from_s(s2, n);
                                    av = (struct AV*)g_global[I_at_INC].value.p;
                                    AV_push(av, sv);
                                    goto done_use;
                                }
                                else{
                                    puts("use lib");
                                    dump_parse_stack(stack, i_top, cur, s);
                                    exit(0);
                                }
                            }
                            char_save = s2[n];
                            s2[n] = '\0';
                            tb_exist = 0;
                            for(i=0; i<modules_len; i++){
                                if(strcmp(modules[i], s2) == 0){
                                    tb_exist = 1;
                                    break;
                                }
                            }
                            if(!tb_exist){
                                if(modules_len + 1 > modules_size){
                                    modules_size = (modules_len + 1) * 5 / 3 + 10;
                                    modules=(char**)realloc(modules, modules_size*sizeof(char*));
                                }
                                memset(modules + modules_len, 0, (1) * sizeof(*modules));
                                modules[modules_len]=(char*)malloc((n+4)*sizeof(char));
                                s3 = s2;
                                i = 0;
                                while(*s3){
                                    if(s3[0]==':' && s3[1]==':'){
                                        modules[modules_len][i++] = '/';
                                        s3 += 2;
                                    }
                                    else{
                                        modules[modules_len][i++] = *s3++;
                                    }
                                }
                                strcpy(modules[modules_len] + i, ".pm");
                                modules_len++;
                            }
                            s2[n] = char_save;
                        }
                        else{
                            puts("use");
                            dump_parse_stack(stack, i_top, cur, s);
                            exit(0);
                        }
                        done_use:
                        s = f_skip_simple_spaces(s);
                        if(!s){
                            s = s_src_end;
                        }
                        if(*s == ';'){
                            s++;
                        }
                        else{
                            puts("semicolon expected after 'use'");
                            dump_parse_stack(stack, i_top, cur, s);
                            exit(0);
                        }
                        goto lexer;
                    }
                    else if(tn_word == WORD_sub){
                        op = get_op();
                        op->type = OP_SUB;
                        op->right.op = NULL;
                        op->right.n = 0;
                        cur.type = T_BOS;
                        cur.value.op = op;
                        goto try_reduce;
                    }
                    else if(tn_word == WORD_if){
                        op = get_op();
                        op->type = OP_IF;
                        op->right.op = NULL;
                        op->right.n = 0;
                        cur.type = T_BOS;
                        cur.value.op = op;
                        goto try_reduce;
                    }
                    else if(tn_word == WORD_while){
                        op = get_op();
                        op->type = OP_while;
                        op->right.op = NULL;
                        op->right.n = 0;
                        cur.type = T_BOS;
                        cur.value.op = op;
                        CV_begin();
                        cv_cur->flag = CVf_loop;
                        goto try_reduce;
                    }
                    else if(tn_word == WORD_for){
                        op = get_op();
                        op->type = OP_for;
                        op->right.op = NULL;
                        op->right.n = 0;
                        cur.type = T_BOS;
                        cur.value.op = op;
                        CV_begin();
                        cv_cur->flag = CVf_loop;
                        goto try_reduce;
                    }
                    else if(tn_word == WORD_my || tn_word == WORD_our){
                        n_in_my = tn_word;
                        cur.type = T_MY;
                        cur.value.n = tn_word;
                        goto try_reduce;
                    }
                    printf("unsupported keyword %.*s\n", n, s2);
                    dump_parse_stack(stack, i_top, cur, s);
                    exit(0);
                }
            }
            s = f_skip_simple_spaces(s);
            if(!s){
                s = s_src_end;
            }
            tn_bos_op = 0;
            tn_unary_word = 0;
            if(stack[i_top-1].type == T_BOS){
                tn_bos_op = stack[i_top-1].value.op->type;
            }
            else if(stack[i_top-1].type==T_FN_LIST ||stack[i_top-1].type==T_FN_1 ){
                tn_unary_word = stack[i_top-1].value.n;
            }
            else if(stack[i_top-1].type == T_BOC && stack[i_top-2].type == T_UNARY){
                tn_unary_word = stack[i_top-2].value.op->left.n;
            }
            if(tn_bos_op == OP_SUB){
                sv = get_sv(SVt_string);
                SV_append_s(sv, "&", 1);
                SV_append_s(sv, s2, n);
                stack[i_top-1].value.op->left.sv = sv;
                goto lexer;
            }
            else if(s && *s == '('){
                sv = get_sv(SVt_string);
                SV_append_s(sv, "&", 1);
                SV_append_s(sv, s2, n);
                op = get_op();
                op->type = OP_Fcall;
                op->left.sv = sv;
                op->right.n = 0;
                cur.type = T_UNARY;
                cur.value.op = op;
                goto try_reduce;
            }
            else if((tn_unary_word == WORD_open || tn_unary_word == WORD_close || tn_unary_word == WORD_print || tn_unary_word == WORD_printf) || (stack[i_top-1].type == T_BOC && stack[i_top-1].value.n == '<')){
                ts_var_buf[0] = '*';
                memcpy(ts_var_buf + 1, s2, n);
                ts_var_buf[n+1] = '\0';
                tn_op_type = OP_GLOBAL;
                i_var = find_global(ts_var_buf);
                if(!i_var){
                    if(tn_unary_word == WORD_open){
                        i_var = g_global_len;
                        if(g_global_len + 1 > g_global_size){
                            g_global_size = (g_global_len + 1) * 5 / 3 + 10;
                            g_global=(struct SV*)realloc(g_global, g_global_size*sizeof(struct SV));
                        }
                        memset(g_global + g_global_len, 0, (1) * sizeof(*g_global));
                        g_global_len++;
                        k = f_strhash_lookup_left(stash_global, (unsigned char*)ts_var_buf, n + 1);
                        stash_global->p_val[k] = i_var;
                        sv_var = &g_global[i_var];
                        if(ts_var_buf[0] == '@'){
                            sv_var->type = SVt_av;
                        }
                        else if(ts_var_buf[0] == '%'){
                            sv_var->type = SVt_hv;
                        }
                        else if(ts_var_buf[0] == '*'){
                            sv_var->type = SVt_io;
                        }
                        else{
                            sv_var->type = SVt_undef;
                        }
                    }
                    else{
                        printf("file handle [%s] not defned\n", ts_var_buf);
                        dump_parse_stack(stack, i_top, cur, s);
                        exit(0);
                    }
                }
                cur.type = T_ATOM;
                cur.value.op = get_op();
                cur.value.op->type = OP_GLOBAL;
                cur.value.op->left.n = '*';
                cur.value.op->right.n = i_var;
                goto do_shift;
            }
            else if(stack[i_top-1].type == T_SIGIL){
                if(has_package){
                    if(n_in_my){
                        puts("package var in my/our");
                        dump_parse_stack(stack, i_top, cur, s);
                        exit(0);
                    }
                    sv = sv_from_s(s2, n);
                    cur.type = T_ATOM;
                    cur.value.op = get_op();
                    cur.value.op->type = OP_CONST;
                    cur.value.op->right.op = NULL;
                    cur.value.op->right.sv = sv;
                    goto do_shift;
                }
                else{
                    char_sigil = stack[i_top-1].value.n;
                    if(char_sigil == '$'){
                        s = f_skip_simple_spaces(s);
                        if(!s){
                            s = s_src_end;
                        }
                        if(*s == '{'){
                            ts_var_buf[0] = '%';
                        }
                        else if(*s == '['){
                            ts_var_buf[0] = '@';
                        }
                        else{
                            ts_var_buf[0] = '$';
                        }
                    }
                    else{
                        ts_var_buf[0] = char_sigil;
                    }
                    memcpy(ts_var_buf + 1, s2, n);
                    ts_var_buf[n+1] = '\0';
                    if(n_in_my == 0){
                        i_var = find_local(ts_var_buf);
                        if(i_var){
                            i_top -= 1;
                            cur.value.op = get_op();
                            cur.value.op->type = OP_LOCAL;
                            cur.value.op->left.n = char_sigil;
                            cur.value.op->right.n = i_var;
                        }
                        else{
                            i_var = find_global(ts_var_buf);
                            if(i_var){
                                i_top -= 1;
                                cur.value.op = get_op();
                                cur.value.op->type = OP_GLOBAL;
                                cur.value.op->left.n = char_sigil;
                                cur.value.op->right.n = i_var;
                            }
                            else{
                                puts("undeclared variable");
                                dump_parse_stack(stack, i_top, cur, s);
                                exit(0);
                            }
                        }
                    }
                    else{
                        if(n_in_my == WORD_our){
                            i_var = find_global(ts_var_buf);
                            if(!i_var){
                                i_var = g_global_len;
                                if(g_global_len + 1 > g_global_size){
                                    g_global_size = (g_global_len + 1) * 5 / 3 + 10;
                                    g_global=(struct SV*)realloc(g_global, g_global_size*sizeof(struct SV));
                                }
                                memset(g_global + g_global_len, 0, (1) * sizeof(*g_global));
                                g_global_len++;
                                k = f_strhash_lookup_left(stash_global, (unsigned char*)ts_var_buf, n + 1);
                                stash_global->p_val[k] = i_var;
                                sv_var = &g_global[i_var];
                                if(ts_var_buf[0] == '@'){
                                    sv_var->type = SVt_av;
                                }
                                else if(ts_var_buf[0] == '%'){
                                    sv_var->type = SVt_hv;
                                }
                                else if(ts_var_buf[0] == '*'){
                                    sv_var->type = SVt_io;
                                }
                                else{
                                    sv_var->type = SVt_undef;
                                }
                            }
                            i_top -= 1;
                            cur.value.op = get_op();
                            cur.value.op->type = OP_GLOBAL;
                            cur.value.op->left.n = char_sigil;
                            cur.value.op->right.n = i_var;
                        }
                        else if(n_in_my == WORD_my){
                            i_var = g_local_len;
                            if(g_local_len + 1 > g_local_size){
                                g_local_size = (g_local_len + 1) * 5 / 3 + 10;
                                g_local=(struct SV*)realloc(g_local, g_local_size*sizeof(struct SV));
                            }
                            memset(g_local + g_local_len, 0, (1) * sizeof(*g_local));
                            g_local_len++;
                            i_str = f_addto_strpool(&local_names, ts_var_buf, n + 1);
                            if(local_vars_len + 1 > local_vars_size){
                                local_vars = f_darray_expand(local_vars, sizeof(int), &local_vars_size);
                            }
                            local_vars[local_vars_len] = i_str;
                            local_vars_len++;
                            if(local_vars_len + 1 > local_vars_size){
                                local_vars = f_darray_expand(local_vars, sizeof(int), &local_vars_size);
                            }
                            local_vars[local_vars_len] = i_var;
                            local_vars_len++;
                            i_top -= 1;
                            cur.value.op = get_op();
                            cur.value.op->type = OP_MY;
                            cur.value.op->left.n = char_sigil;
                            cur.value.op->right.n = i_var;
                        }
                    }
                    cur.type = T_ATOM;
                    goto do_shift;
                }
            }
            else if(s && *s == ':'){
                if(stack[i_top-1].type == T_BOC || stack[i_top-1].type == T_Semi){
                    if(s2 + n < s){
                        s2[n] = ':';
                    }
                    s++;
                    n++;
                    k = f_strhash_lookup_left(stash_local, (unsigned char*)s2, n);
                    stash_local->p_val[k] = i_seq;
                    goto lexer;
                }
            }
            if(s && strncmp(s, "=>", 2) == 0){
                sv = sv_from_s(s2, n);
                cur.type = T_ATOM;
                cur.value.op = get_op();
                cur.value.op->type = OP_CONST;
                cur.value.op->right.op = NULL;
                cur.value.op->right.sv = sv;
                goto do_shift;
            }
            else if(s && *s == '}' && stack[i_top-1].type == T_BOC){
                sv = sv_from_s(s2, n);
                cur.type = T_ATOM;
                cur.value.op = get_op();
                cur.value.op->type = OP_CONST;
                cur.value.op->right.op = NULL;
                cur.value.op->right.sv = sv;
                goto do_shift;
            }
            printf("bareword %.*s [%d]\n", n, s2, tn_unary_word);
            dump_parse_stack(stack, i_top, cur, s);
            exit(0);
        }
        else if((stack[i_top-1].type & 0xffff00) && (*s=='$' || *s=='@' || *s=='%')){
            char_sigil = *s++;
            op = f_parse_var_special(char_sigil, s);
            if(op){
                cur.type = T_ATOM;
                cur.value.op = op;
                goto do_shift;
            }
            else{
                cur.type = T_SIGIL;
                cur.value.n = char_sigil;
                goto try_reduce;
            }
        }
        else if((*s=='(' || *s=='{' || *s=='[')){
            cur.type = T_BOC;
            cur.value.n = *s;
            s++;
            goto do_shift;
        }
        else if((*s==')' || *s=='}' || *s==']')){
            cur.type = T_EOC;
            cur.value.n = *s;
            s++;
            goto try_reduce;
        }
        else{
            tn_op = 0;
            s = f_scan_operator(s, &tn_op);
            if(tn_op > 0){
                cur.type = tn_op;
                cur.value.n = 0;
                goto try_reduce;
            }
            else{
                puts("symbol not matched");
                dump_parse_stack(stack, i_top, cur, s);
                exit(0);
            }
        }
        puts("unexpected char");
        dump_parse_stack(stack, i_top, cur, s);
        exit(0);
        try_reduce:
        if(!((cur.type & 0xffff00))){
            puts("assert error: ! ((cur.type & 0xffff00))");
            exit(0);
        }
        if(cur.type == T_Semi){
            if(local_vars_len > 0){
                int i;
                p_strpool = &local_names;
                for(i=0; i<local_vars_len; i+=2){
                    k = f_strhash_lookup_left(stash_local, (unsigned char*)(p_strpool->pc_pool + p_strpool->pn_str[local_vars[i]]), (p_strpool->pn_str[local_vars[i]+1] - p_strpool->pn_str[local_vars[i]] - 1));
                    stash_local->p_val[k] = local_vars[i+1];
                }
                local_vars_len = 0;
                p_strpool->i_str = 0;
                p_strpool->i_pool = 0;
            }
        }
        if(stack[i_top-1].type & 0xffff00){
            if((cur.type & 3) == 2){
                goto do_shift;
            }
            else{
                if(cur.type == T_Lt){
                    cur.type = T_BOC;
                    cur.value.n = '<';
                    goto do_shift;
                }
                else if(cur.type == T_EOF){
                    if(i_top == 1){
                        stack[0].type = T_ATOM;
                        break;
                    }
                    else{
                        break;
                    }
                }
                else if((cur.type == T_EOC || cur.type == T_EOF) && stack[i_top-1].type == T_Semi){
                    i_top--;
                    goto try_reduce;
                }
                else if(cur.type == T_EOC && stack[i_top-1].type == T_BOC){
                    i_top -= 1;
                    cur.type = T_ATOM;
                    cur.value.op = NULL;
                    goto do_shift;
                }
                puts("unexpected operator!");
                dump_parse_stack(stack, i_top, cur, s);
                exit(0);
            }
        }
        else{
            if((cur.type & 3) == 2){
                if(cur.type == T_PlusPlus || cur.type == T_MinusMinus){
                    if(cur.type == T_PlusPlus){
                        tn_op = OP_INC;
                    }
                    else{
                        tn_op = OP_DEC;
                    }
                    if(stack[i_top-1].type == T_ATOM){
                        op = get_op();
                        op->type = tn_op;
                        op->right.op = NULL;
                        op->right.op = stack[i_top-1].value.op;
                    }
                    else{
                        printf("postfix ++/-");
                        dump_parse_stack(stack, i_top, cur, s);
                        exit(0);
                    }
                    stack[i_top-1].value.op = op;
                    goto lexer;
                }
                puts("unexpected unary operator");
                dump_parse_stack(stack, i_top, cur, s);
                exit(0);
            }
        }
        if(cur.type == T_Gt){
            if(stack[i_top-1].type == T_BOC && stack[i_top-1].value.n == '<'){
                op_fh = get_op();
                op_fh->type = OP_GLOBAL;
                op_fh->right.op = NULL;
                op_fh->right.n = I_STDIN;
                op = get_op();
                op->type = OP_UNARY;
                op->left.n = WORD_fread;
                op->right.op = op_fh;
                if(stack[i_top-2].type != T_Eq){
                    op_fread = op;
                    op_var = get_op();
                    op_var->type = OP_GLOBAL;
                    op_var->left.n = '$';
                    op_var->right.n = I_ARG;
                    op = get_op();
                    op->type = OP_ASSIGN;
                    op->left.op = op_var;
                    op->right.op = op_fread;
                }
                stack[i_top-1].type = T_ATOM;
                stack[i_top-1].value.op = op;
                goto lexer;
            }
            else if(stack[i_top-2].type == T_BOC && stack[i_top-2].value.n == '<'){
                if(!(stack[i_top-1].type == T_ATOM)){
                    puts("assert error: ! (stack[i_top-1].type==T_ATOM)");
                    exit(0);
                }
                op = get_op();
                op->type = OP_UNARY;
                op->left.n = WORD_fread;
                op->right.op = stack[i_top-1].value.op;
                i_top--;
                if(stack[i_top-2].type != T_Eq){
                    op_fread = op;
                    op_var = get_op();
                    op_var->type = OP_GLOBAL;
                    op_var->left.n = '$';
                    op_var->right.n = I_ARG;
                    op = get_op();
                    op->type = OP_ASSIGN;
                    op->left.op = op_var;
                    op->right.op = op_fread;
                }
                stack[i_top-1].type = T_ATOM;
                stack[i_top-1].value.op = op;
                goto lexer;
            }
        }
        if(i_top <= 1){
            goto do_shift;
        }
        if((cur.type & 0xff) < (stack[i_top-2].type & 0xff) || ((cur.type & 0xff) == (stack[i_top-2].type & 0xff) && (cur.type & 3) == 0)){
            if((stack[i_top-2].type & 3) == 2){
                if(stack[i_top-2].type == T_FN_GOTO){
                    if(stack[i_top-2].value.n == WORD_goto){
                        op = get_op();
                        op->type = OP_GOTO_LABEL;
                        op->right.op = NULL;
                        op->right.op = stack[i_top-1].value.op;
                    }
                    else if(stack[i_top-2].value.n == WORD_return){
                        if(cv_cur->flag == CVf_sub){
                            cv = cv_cur;
                        }
                        else{
                            i = lex_stack_len - 1;
                            while(i>0){
                                if(lex_stack[i]->flag == CVf_sub){
                                    cv = lex_stack[i];
                                    break;
                                }
                                i--;
                            }
                            if(i == 0){
                                puts("return outside sub");
                                dump_parse_stack(stack, i_top, cur, s);
                                exit(0);
                            }
                        }
                        op = get_op();
                        op->type = OP_RETURN;
                        op->left.cv = cv;
                        op->right.op = stack[i_top-1].value.op;
                    }
                    else{
                        if(!stack[i_top-1].value.op){
                            i = lex_stack_len - 1;
                            cv = lex_stack[i];
                            while(i>0){
                                if(lex_stack[i]->flag == CVf_loop){
                                    cv = lex_stack[i];
                                    break;
                                }
                                i--;
                            }
                            if(stack[i_top-2].value.n == WORD_next){
                                tn_i = GOTO_next;
                            }
                            else if(stack[i_top-2].value.n == WORD_last){
                                tn_i = GOTO_last;
                            }
                            else if(stack[i_top-2].value.n == WORD_redo){
                                tn_i = GOTO_redo;
                            }
                            op = get_op();
                            op->type = OP_GOTO;
                            op->left.cv = cv;
                            op->right.n = tn_i;
                        }
                        else{
                        }
                    }
                }
                else if(stack[i_top-2].type == T_FN_LIST || stack[i_top-2].type == T_FN_1){
                    op = get_op();
                    op->type = OP_UNARY;
                    op->left.n = stack[i_top-2].value.n;
                    op->right.op = stack[i_top-1].value.op;
                }
                else if(stack[i_top-2].type == T_UNARY){
                    op = stack[i_top-2].value.op;
                    if(op->type == OP_Fcall){
                        op->right.op = stack[i_top-1].value.op;
                    }
                    else{
                        op->type = OP_UNARY;
                        op->right.op = stack[i_top-1].value.op;
                    }
                }
                else{
                    switch (stack[i_top-2].type){
                        case T_UMINUS:
                            op = get_op();
                            op->type = OP_UMINUS;
                            op->right.op = NULL;
                            op->right.op = stack[i_top-1].value.op;
                            break;
                        case T_Emark:
                        case T_not:
                            op = get_op();
                            op->type = OP_NOT;
                            op->right.op = NULL;
                            op->right.op = stack[i_top-1].value.op;
                            break;
                        case T_PlusPlus:
                        case T_MinusMinus:
                            if(stack[i_top-2].type == T_PlusPlus){
                                tn_op = OP_PlusEq;
                            }
                            else{
                                tn_op = OP_MinusEq;
                            }
                            if(stack[i_top-1].type == T_ATOM){
                                op_b = get_op();
                                op_b->type = OP_CONST;
                                op_b->right.op = NULL;
                                op_b->right.sv = sv_TRUE;
                                op = get_op();
                                op->type = tn_op;
                                op->left.op = stack[i_top-1].value.op;
                                op->right.op = op_b;
                            }
                            else{
                                printf("prefix ++/-");
                                dump_parse_stack(stack, i_top, cur, s);
                                exit(0);
                            }
                            break;
                        case T_MY:
                            op = stack[i_top-1].value.op;
                            n_in_my = 0;
                            break;
                        case T_SIGIL:
                            char_sigil = stack[i_top-2].value.n;
                            op = get_op();
                            op->type = OP_SIGIL;
                            op->left.n = char_sigil;
                            op->right.op = stack[i_top-1].value.op;
                            break;
                        default:
                            puts("unsupported prefix");
                            dump_parse_stack(stack, i_top, cur, s);
                            exit(0);
                    }
                }
                if(n_debug){
                    int i;
                    for(i=0; i<i_top-2; i++){
                        fputs(".", stdout);
                    }
                    puts("reduce_unary T_ATOM");
                }
                stack[i_top-2].type = T_ATOM;
                stack[i_top-2].value.op = op;
                i_top -= 1;
                goto try_reduce;
            }
            else{
                switch (stack[i_top-2].type){
                    case T_Semi:
                        if(n_debug){
                            int i;
                            for(i=0; i<i_top-2; i++){
                                fputs(".", stdout);
                            }
                            printf("reduce_binary: OP_SEQ -> %s, %s\n", get_OP_name(stack[i_top-3].value.op->type), get_OP_name(stack[i_top-1].value.op->type));
                        }
                        op = f_new_op(OP_SEQ, stack[i_top-3].value.op, stack[i_top-1].value.op);
                        break;
                    case T_Comma:
                        if(n_debug){
                            int i;
                            for(i=0; i<i_top-2; i++){
                                fputs(".", stdout);
                            }
                            printf("reduce_binary: OP_LIST -> %s, %s\n", get_OP_name(stack[i_top-3].value.op->type), get_OP_name(stack[i_top-1].value.op->type));
                        }
                        op = f_new_op(OP_LIST, stack[i_top-3].value.op, stack[i_top-1].value.op);
                        break;
                    case T_Eq:
                        if(n_debug){
                            int i;
                            for(i=0; i<i_top-2; i++){
                                fputs(".", stdout);
                            }
                            printf("reduce_binary: OP_ASSIGN -> %s, %s\n", get_OP_name(stack[i_top-3].value.op->type), get_OP_name(stack[i_top-1].value.op->type));
                        }
                        op = f_new_op(OP_ASSIGN, stack[i_top-3].value.op, stack[i_top-1].value.op);
                        break;
                    case T_Plus:
                        if(n_debug){
                            int i;
                            for(i=0; i<i_top-2; i++){
                                fputs(".", stdout);
                            }
                            printf("reduce_binary: OP_Plus -> %s, %s\n", get_OP_name(stack[i_top-3].value.op->type), get_OP_name(stack[i_top-1].value.op->type));
                        }
                        op = f_new_op(OP_Plus, stack[i_top-3].value.op, stack[i_top-1].value.op);
                        break;
                    case T_Minus:
                        if(n_debug){
                            int i;
                            for(i=0; i<i_top-2; i++){
                                fputs(".", stdout);
                            }
                            printf("reduce_binary: OP_Minus -> %s, %s\n", get_OP_name(stack[i_top-3].value.op->type), get_OP_name(stack[i_top-1].value.op->type));
                        }
                        op = f_new_op(OP_Minus, stack[i_top-3].value.op, stack[i_top-1].value.op);
                        break;
                    case T_Mult:
                        if(n_debug){
                            int i;
                            for(i=0; i<i_top-2; i++){
                                fputs(".", stdout);
                            }
                            printf("reduce_binary: OP_Mult -> %s, %s\n", get_OP_name(stack[i_top-3].value.op->type), get_OP_name(stack[i_top-1].value.op->type));
                        }
                        op = f_new_op(OP_Mult, stack[i_top-3].value.op, stack[i_top-1].value.op);
                        break;
                    case T_Div:
                        if(n_debug){
                            int i;
                            for(i=0; i<i_top-2; i++){
                                fputs(".", stdout);
                            }
                            printf("reduce_binary: OP_Div -> %s, %s\n", get_OP_name(stack[i_top-3].value.op->type), get_OP_name(stack[i_top-1].value.op->type));
                        }
                        op = f_new_op(OP_Div, stack[i_top-3].value.op, stack[i_top-1].value.op);
                        break;
                    case T_Mod:
                        if(n_debug){
                            int i;
                            for(i=0; i<i_top-2; i++){
                                fputs(".", stdout);
                            }
                            printf("reduce_binary: OP_Mod -> %s, %s\n", get_OP_name(stack[i_top-3].value.op->type), get_OP_name(stack[i_top-1].value.op->type));
                        }
                        op = f_new_op(OP_Mod, stack[i_top-3].value.op, stack[i_top-1].value.op);
                        break;
                    case T_Or:
                        if(n_debug){
                            int i;
                            for(i=0; i<i_top-2; i++){
                                fputs(".", stdout);
                            }
                            printf("reduce_binary: OP_Or -> %s, %s\n", get_OP_name(stack[i_top-3].value.op->type), get_OP_name(stack[i_top-1].value.op->type));
                        }
                        op = f_new_op(OP_Or, stack[i_top-3].value.op, stack[i_top-1].value.op);
                        break;
                    case T_And:
                        if(n_debug){
                            int i;
                            for(i=0; i<i_top-2; i++){
                                fputs(".", stdout);
                            }
                            printf("reduce_binary: OP_And -> %s, %s\n", get_OP_name(stack[i_top-3].value.op->type), get_OP_name(stack[i_top-1].value.op->type));
                        }
                        op = f_new_op(OP_And, stack[i_top-3].value.op, stack[i_top-1].value.op);
                        break;
                    case T_Ctrl:
                        if(n_debug){
                            int i;
                            for(i=0; i<i_top-2; i++){
                                fputs(".", stdout);
                            }
                            printf("reduce_binary: OP_Ctrl -> %s, %s\n", get_OP_name(stack[i_top-3].value.op->type), get_OP_name(stack[i_top-1].value.op->type));
                        }
                        op = f_new_op(OP_Ctrl, stack[i_top-3].value.op, stack[i_top-1].value.op);
                        break;
                    case T_GtGt:
                        if(n_debug){
                            int i;
                            for(i=0; i<i_top-2; i++){
                                fputs(".", stdout);
                            }
                            printf("reduce_binary: OP_GtGt -> %s, %s\n", get_OP_name(stack[i_top-3].value.op->type), get_OP_name(stack[i_top-1].value.op->type));
                        }
                        op = f_new_op(OP_GtGt, stack[i_top-3].value.op, stack[i_top-1].value.op);
                        break;
                    case T_LtLt:
                        if(n_debug){
                            int i;
                            for(i=0; i<i_top-2; i++){
                                fputs(".", stdout);
                            }
                            printf("reduce_binary: OP_LtLt -> %s, %s\n", get_OP_name(stack[i_top-3].value.op->type), get_OP_name(stack[i_top-1].value.op->type));
                        }
                        op = f_new_op(OP_LtLt, stack[i_top-3].value.op, stack[i_top-1].value.op);
                        break;
                    case T_EqEq:
                        if(n_debug){
                            int i;
                            for(i=0; i<i_top-2; i++){
                                fputs(".", stdout);
                            }
                            printf("reduce_binary: OP_EqEq -> %s, %s\n", get_OP_name(stack[i_top-3].value.op->type), get_OP_name(stack[i_top-1].value.op->type));
                        }
                        op = f_new_op(OP_EqEq, stack[i_top-3].value.op, stack[i_top-1].value.op);
                        break;
                    case T_EmarkEq:
                        if(n_debug){
                            int i;
                            for(i=0; i<i_top-2; i++){
                                fputs(".", stdout);
                            }
                            printf("reduce_binary: OP_EmarkEq -> %s, %s\n", get_OP_name(stack[i_top-3].value.op->type), get_OP_name(stack[i_top-1].value.op->type));
                        }
                        op = f_new_op(OP_EmarkEq, stack[i_top-3].value.op, stack[i_top-1].value.op);
                        break;
                    case T_Lt:
                        if(n_debug){
                            int i;
                            for(i=0; i<i_top-2; i++){
                                fputs(".", stdout);
                            }
                            printf("reduce_binary: OP_Lt -> %s, %s\n", get_OP_name(stack[i_top-3].value.op->type), get_OP_name(stack[i_top-1].value.op->type));
                        }
                        op = f_new_op(OP_Lt, stack[i_top-3].value.op, stack[i_top-1].value.op);
                        break;
                    case T_Gt:
                        if(n_debug){
                            int i;
                            for(i=0; i<i_top-2; i++){
                                fputs(".", stdout);
                            }
                            printf("reduce_binary: OP_Gt -> %s, %s\n", get_OP_name(stack[i_top-3].value.op->type), get_OP_name(stack[i_top-1].value.op->type));
                        }
                        op = f_new_op(OP_Gt, stack[i_top-3].value.op, stack[i_top-1].value.op);
                        break;
                    case T_LtEq:
                        if(n_debug){
                            int i;
                            for(i=0; i<i_top-2; i++){
                                fputs(".", stdout);
                            }
                            printf("reduce_binary: OP_LtEq -> %s, %s\n", get_OP_name(stack[i_top-3].value.op->type), get_OP_name(stack[i_top-1].value.op->type));
                        }
                        op = f_new_op(OP_LtEq, stack[i_top-3].value.op, stack[i_top-1].value.op);
                        break;
                    case T_GtEq:
                        if(n_debug){
                            int i;
                            for(i=0; i<i_top-2; i++){
                                fputs(".", stdout);
                            }
                            printf("reduce_binary: OP_GtEq -> %s, %s\n", get_OP_name(stack[i_top-3].value.op->type), get_OP_name(stack[i_top-1].value.op->type));
                        }
                        op = f_new_op(OP_GtEq, stack[i_top-3].value.op, stack[i_top-1].value.op);
                        break;
                    case T_LtEqGt:
                        if(n_debug){
                            int i;
                            for(i=0; i<i_top-2; i++){
                                fputs(".", stdout);
                            }
                            printf("reduce_binary: OP_LtEqGt -> %s, %s\n", get_OP_name(stack[i_top-3].value.op->type), get_OP_name(stack[i_top-1].value.op->type));
                        }
                        op = f_new_op(OP_LtEqGt, stack[i_top-3].value.op, stack[i_top-1].value.op);
                        break;
                    case T_x:
                        if(n_debug){
                            int i;
                            for(i=0; i<i_top-2; i++){
                                fputs(".", stdout);
                            }
                            printf("reduce_binary: OP_x -> %s, %s\n", get_OP_name(stack[i_top-3].value.op->type), get_OP_name(stack[i_top-1].value.op->type));
                        }
                        op = f_new_op(OP_x, stack[i_top-3].value.op, stack[i_top-1].value.op);
                        break;
                    case T_Dot:
                        if(n_debug){
                            int i;
                            for(i=0; i<i_top-2; i++){
                                fputs(".", stdout);
                            }
                            printf("reduce_binary: OP_Dot -> %s, %s\n", get_OP_name(stack[i_top-3].value.op->type), get_OP_name(stack[i_top-1].value.op->type));
                        }
                        op = f_new_op(OP_Dot, stack[i_top-3].value.op, stack[i_top-1].value.op);
                        break;
                    case T_eq:
                        if(n_debug){
                            int i;
                            for(i=0; i<i_top-2; i++){
                                fputs(".", stdout);
                            }
                            printf("reduce_binary: OP_eq -> %s, %s\n", get_OP_name(stack[i_top-3].value.op->type), get_OP_name(stack[i_top-1].value.op->type));
                        }
                        op = f_new_op(OP_eq, stack[i_top-3].value.op, stack[i_top-1].value.op);
                        break;
                    case T_ne:
                        if(n_debug){
                            int i;
                            for(i=0; i<i_top-2; i++){
                                fputs(".", stdout);
                            }
                            printf("reduce_binary: OP_ne -> %s, %s\n", get_OP_name(stack[i_top-3].value.op->type), get_OP_name(stack[i_top-1].value.op->type));
                        }
                        op = f_new_op(OP_ne, stack[i_top-3].value.op, stack[i_top-1].value.op);
                        break;
                    case T_lt:
                        if(n_debug){
                            int i;
                            for(i=0; i<i_top-2; i++){
                                fputs(".", stdout);
                            }
                            printf("reduce_binary: OP_lt -> %s, %s\n", get_OP_name(stack[i_top-3].value.op->type), get_OP_name(stack[i_top-1].value.op->type));
                        }
                        op = f_new_op(OP_lt, stack[i_top-3].value.op, stack[i_top-1].value.op);
                        break;
                    case T_gt:
                        if(n_debug){
                            int i;
                            for(i=0; i<i_top-2; i++){
                                fputs(".", stdout);
                            }
                            printf("reduce_binary: OP_gt -> %s, %s\n", get_OP_name(stack[i_top-3].value.op->type), get_OP_name(stack[i_top-1].value.op->type));
                        }
                        op = f_new_op(OP_gt, stack[i_top-3].value.op, stack[i_top-1].value.op);
                        break;
                    case T_le:
                        if(n_debug){
                            int i;
                            for(i=0; i<i_top-2; i++){
                                fputs(".", stdout);
                            }
                            printf("reduce_binary: OP_le -> %s, %s\n", get_OP_name(stack[i_top-3].value.op->type), get_OP_name(stack[i_top-1].value.op->type));
                        }
                        op = f_new_op(OP_le, stack[i_top-3].value.op, stack[i_top-1].value.op);
                        break;
                    case T_ge:
                        if(n_debug){
                            int i;
                            for(i=0; i<i_top-2; i++){
                                fputs(".", stdout);
                            }
                            printf("reduce_binary: OP_ge -> %s, %s\n", get_OP_name(stack[i_top-3].value.op->type), get_OP_name(stack[i_top-1].value.op->type));
                        }
                        op = f_new_op(OP_ge, stack[i_top-3].value.op, stack[i_top-1].value.op);
                        break;
                    case T_cmp:
                        if(n_debug){
                            int i;
                            for(i=0; i<i_top-2; i++){
                                fputs(".", stdout);
                            }
                            printf("reduce_binary: OP_cmp -> %s, %s\n", get_OP_name(stack[i_top-3].value.op->type), get_OP_name(stack[i_top-1].value.op->type));
                        }
                        op = f_new_op(OP_cmp, stack[i_top-3].value.op, stack[i_top-1].value.op);
                        break;
                    case T_PlusEq:
                        if(n_debug){
                            int i;
                            for(i=0; i<i_top-2; i++){
                                fputs(".", stdout);
                            }
                            printf("reduce_binary: OP_PlusEq -> %s, %s\n", get_OP_name(stack[i_top-3].value.op->type), get_OP_name(stack[i_top-1].value.op->type));
                        }
                        op = f_new_op(OP_PlusEq, stack[i_top-3].value.op, stack[i_top-1].value.op);
                        break;
                    case T_MinusEq:
                        if(n_debug){
                            int i;
                            for(i=0; i<i_top-2; i++){
                                fputs(".", stdout);
                            }
                            printf("reduce_binary: OP_MinusEq -> %s, %s\n", get_OP_name(stack[i_top-3].value.op->type), get_OP_name(stack[i_top-1].value.op->type));
                        }
                        op = f_new_op(OP_MinusEq, stack[i_top-3].value.op, stack[i_top-1].value.op);
                        break;
                    case T_MultEq:
                        if(n_debug){
                            int i;
                            for(i=0; i<i_top-2; i++){
                                fputs(".", stdout);
                            }
                            printf("reduce_binary: OP_MultEq -> %s, %s\n", get_OP_name(stack[i_top-3].value.op->type), get_OP_name(stack[i_top-1].value.op->type));
                        }
                        op = f_new_op(OP_MultEq, stack[i_top-3].value.op, stack[i_top-1].value.op);
                        break;
                    case T_DivEq:
                        if(n_debug){
                            int i;
                            for(i=0; i<i_top-2; i++){
                                fputs(".", stdout);
                            }
                            printf("reduce_binary: OP_DivEq -> %s, %s\n", get_OP_name(stack[i_top-3].value.op->type), get_OP_name(stack[i_top-1].value.op->type));
                        }
                        op = f_new_op(OP_DivEq, stack[i_top-3].value.op, stack[i_top-1].value.op);
                        break;
                    case T_ModEq:
                        if(n_debug){
                            int i;
                            for(i=0; i<i_top-2; i++){
                                fputs(".", stdout);
                            }
                            printf("reduce_binary: OP_ModEq -> %s, %s\n", get_OP_name(stack[i_top-3].value.op->type), get_OP_name(stack[i_top-1].value.op->type));
                        }
                        op = f_new_op(OP_ModEq, stack[i_top-3].value.op, stack[i_top-1].value.op);
                        break;
                    case T_OrEq:
                        if(n_debug){
                            int i;
                            for(i=0; i<i_top-2; i++){
                                fputs(".", stdout);
                            }
                            printf("reduce_binary: OP_OrEq -> %s, %s\n", get_OP_name(stack[i_top-3].value.op->type), get_OP_name(stack[i_top-1].value.op->type));
                        }
                        op = f_new_op(OP_OrEq, stack[i_top-3].value.op, stack[i_top-1].value.op);
                        break;
                    case T_AndEq:
                        if(n_debug){
                            int i;
                            for(i=0; i<i_top-2; i++){
                                fputs(".", stdout);
                            }
                            printf("reduce_binary: OP_AndEq -> %s, %s\n", get_OP_name(stack[i_top-3].value.op->type), get_OP_name(stack[i_top-1].value.op->type));
                        }
                        op = f_new_op(OP_AndEq, stack[i_top-3].value.op, stack[i_top-1].value.op);
                        break;
                    case T_CtrlEq:
                        if(n_debug){
                            int i;
                            for(i=0; i<i_top-2; i++){
                                fputs(".", stdout);
                            }
                            printf("reduce_binary: OP_CtrlEq -> %s, %s\n", get_OP_name(stack[i_top-3].value.op->type), get_OP_name(stack[i_top-1].value.op->type));
                        }
                        op = f_new_op(OP_CtrlEq, stack[i_top-3].value.op, stack[i_top-1].value.op);
                        break;
                    case T_GtGtEq:
                        if(n_debug){
                            int i;
                            for(i=0; i<i_top-2; i++){
                                fputs(".", stdout);
                            }
                            printf("reduce_binary: OP_GtGtEq -> %s, %s\n", get_OP_name(stack[i_top-3].value.op->type), get_OP_name(stack[i_top-1].value.op->type));
                        }
                        op = f_new_op(OP_GtGtEq, stack[i_top-3].value.op, stack[i_top-1].value.op);
                        break;
                    case T_LtLtEq:
                        if(n_debug){
                            int i;
                            for(i=0; i<i_top-2; i++){
                                fputs(".", stdout);
                            }
                            printf("reduce_binary: OP_LtLtEq -> %s, %s\n", get_OP_name(stack[i_top-3].value.op->type), get_OP_name(stack[i_top-1].value.op->type));
                        }
                        op = f_new_op(OP_LtLtEq, stack[i_top-3].value.op, stack[i_top-1].value.op);
                        break;
                    case T_DotEq:
                        if(n_debug){
                            int i;
                            for(i=0; i<i_top-2; i++){
                                fputs(".", stdout);
                            }
                            printf("reduce_binary: OP_DotEq -> %s, %s\n", get_OP_name(stack[i_top-3].value.op->type), get_OP_name(stack[i_top-1].value.op->type));
                        }
                        op = f_new_op(OP_DotEq, stack[i_top-3].value.op, stack[i_top-1].value.op);
                        break;
                    case T_OrOr:
                        if(n_debug){
                            int i;
                            for(i=0; i<i_top-2; i++){
                                fputs(".", stdout);
                            }
                            printf("reduce_binary: OP_or -> %s, %s\n", get_OP_name(stack[i_top-3].value.op->type), get_OP_name(stack[i_top-1].value.op->type));
                        }
                        op = f_new_op(OP_or, stack[i_top-3].value.op, stack[i_top-1].value.op);
                        break;
                    case T_AndAnd:
                        if(n_debug){
                            int i;
                            for(i=0; i<i_top-2; i++){
                                fputs(".", stdout);
                            }
                            printf("reduce_binary: OP_and -> %s, %s\n", get_OP_name(stack[i_top-3].value.op->type), get_OP_name(stack[i_top-1].value.op->type));
                        }
                        op = f_new_op(OP_and, stack[i_top-3].value.op, stack[i_top-1].value.op);
                        break;
                    case T_or:
                        if(n_debug){
                            int i;
                            for(i=0; i<i_top-2; i++){
                                fputs(".", stdout);
                            }
                            printf("reduce_binary: OP_or -> %s, %s\n", get_OP_name(stack[i_top-3].value.op->type), get_OP_name(stack[i_top-1].value.op->type));
                        }
                        op = f_new_op(OP_or, stack[i_top-3].value.op, stack[i_top-1].value.op);
                        break;
                    case T_and:
                        if(n_debug){
                            int i;
                            for(i=0; i<i_top-2; i++){
                                fputs(".", stdout);
                            }
                            printf("reduce_binary: OP_and -> %s, %s\n", get_OP_name(stack[i_top-3].value.op->type), get_OP_name(stack[i_top-1].value.op->type));
                        }
                        op = f_new_op(OP_and, stack[i_top-3].value.op, stack[i_top-1].value.op);
                        break;
                    default:
                        printf("unsupported binary op [%s]\n", get_OP_name(stack[i_top-2].type));
                        dump_parse_stack(stack, i_top, cur, s);
                        exit(0);
                        break;
                }
                stack[i_top-3].value.op = op;
                i_top -= 2;
                goto try_reduce;
            }
            puts("Don't know how to reduce");
            dump_parse_stack(stack, i_top, cur, s);
            exit(0);
        }
        else if((cur.type & 3) == 3){
            if(cur.type == T_EOF){
                if(i_top == 2){
                    memcpy(stack + 0, stack + 1, sizeof(struct TOK));
                    return 1;
                }
                else{
                    return i_top;
                }
            }
            else if(cur.type == T_EOC){
                if(n_debug){
                    int i;
                    for(i=0; i<i_top-2; i++){
                        fputs(".", stdout);
                    }
                    printf("reduce_eoc %c - %c\n", stack[i_top-2].value.n, cur.value.n);
                    if(stack[i_top-1].value.op->type == OP_LIST){
                        printf(" %p [block: %s -> %s, %s]\n", stack[i_top-1].value.op, get_OP_name(stack[i_top-1].value.op->type), get_OP_name(stack[i_top-1].value.op->left.op->type), get_OP_name(stack[i_top-1].value.op->right.op->type));
                    }
                }
                if(cur.value.n == 0){
                    if(i_top == 2){
                        memcpy(stack + 0, stack + 1, sizeof(struct TOK));
                        return 1;
                    }
                    else{
                        return i_top;
                    }
                }
                else{
                    if((stack[i_top-2].value.n == '(' && cur.value.n == ')') || (stack[i_top-2].value.n == '[' && cur.value.n == ']') || (stack[i_top-2].value.n == '{' && cur.value.n == '}')){
                    }
                    else{
                        puts("Parentheses mismatch!");
                        dump_parse_stack(stack, i_top, cur, s);
                        exit(0);
                    }
                    if((cur.value.n=='}' || cur.value.n==']')){
                        if(stack[i_top-3].type == T_ATOM){
                            tn_type = stack[i_top-3].value.op->type;
                            if(tn_type==OP_SIGIL ||tn_type==OP_LOCAL ||tn_type==OP_GLOBAL ){
                                tn_type = 0;
                                if(cur.value.n == ']'){
                                    tn_type = OP_ARRAY_INDEX;
                                }
                                else if(cur.value.n == '}'){
                                    tn_type = OP_HASH_INDEX;
                                }
                                char_index = cur.value.n;
                                op_index = stack[i_top-1].value.op;
                                i_top -= 2;
                                while(stack[i_top-2].type == T_SIGIL){
                                    char_sigil = stack[i_top-2].value.n;
                                    if(char_sigil != '$'){
                                        puts("var index is scalar (use $)!");
                                        dump_parse_stack(stack, i_top, cur, s);
                                        exit(0);
                                    }
                                    if(tn_type == OP_ARRAY_INDEX){
                                        char_sigil = '@';
                                    }
                                    else if(tn_type == OP_HASH_INDEX){
                                        char_sigil = '%';
                                    }
                                    op_v = get_op();
                                    op_v->type = OP_SIGIL;
                                    op_v->left.n = char_sigil;
                                    op_v->right.op = stack[i_top-1].value.op;
                                    stack[i_top-2].type = T_ATOM;
                                    stack[i_top-2].value.op = op_v;
                                    i_top -= 1;
                                }
                                op_v = f_new_op(tn_type, stack[i_top-1].value.op, op_index);
                                stack[i_top-1].value.op = op_v;
                                cur.type = 0;
                                break;
                            }
                        }
                    }
                    if(cur.value.n == '}'){
                        cv = CV_close(stack[i_top-1].value.op);
                        cur.type = T_ATOM;
                        cur.value.op = get_op();
                        cur.value.op->type = OP_CV;
                        cur.value.op->right.op = NULL;
                        cur.value.op->right.cv = cv;
                        i_top -= 2;
                        s = f_skip_simple_spaces(s);
                        if(!s){
                            s = s_src_end;
                        }
                        if(stack[i_top-1].type==T_Semi ||stack[i_top-1].type==T_BOC ){
                            stack[i_top++] = cur;
                            cur.type = T_Semi;
                            cur.value.n = 0;
                            goto try_reduce;
                        }
                        else if(stack[i_top-1].type == T_BOS){
                            if(stack[i_top-1].value.op->type == OP_SUB){
                                sv_name = stack[i_top-1].value.op->left.sv;
                                k = f_strhash_lookup_left(stash_global, (unsigned char*)sv_name->value.S.s, sv_name->value.S.n);
                                stash_global->p_val[k] = subs_len;
                                if(subs_len + 1 > subs_size){
                                    subs = f_darray_expand(subs, sizeof(struct CV*), &subs_size);
                                }
                                subs[subs_len] = cv;
                                subs_len++;
                                i_top -= 1;
                                goto lexer;
                            }
                            else if(stack[i_top-1].value.op->type == OP_ELSE){
                                stack[i_top-1].value.op->type = OP_IF;
                                op = f_new_op(OP_IF, stack[i_top-1].value.op, cur.value.op);
                                stack[i_top-1].value.op = op;
                                f_flatten_op_list(op, OP_IF);
                                stack[i_top-1].type = T_ATOM;
                                cur.type = T_Semi;
                                cur.value.n = 0;
                                goto try_reduce;
                            }
                            puts("cv1");
                            dump_parse_stack(stack, i_top, cur, s);
                            exit(0);
                        }
                        else if(stack[i_top-2].type == T_BOS){
                            if(stack[i_top-2].value.op->type == OP_IF || stack[i_top-2].value.op->type == OP_ELIF){
                                if(stack[i_top-2].value.op->type == OP_IF){
                                    op = stack[i_top-2].value.op;
                                    op->left.op = stack[i_top-1].value.op;
                                    op->right.op = cur.value.op;
                                }
                                else{
                                    stack[i_top-2].value.op->type = OP_IF;
                                    op_tmp = f_new_op(OP_IF, stack[i_top-2].value.op, stack[i_top-1].value.op);
                                    op = f_new_op(OP_IF, op_tmp, cur.value.op);
                                    stack[i_top-2].value.op = op;
                                }
                                if(strncmp(s, "else", 4) == 0 && !isword(s[4])){
                                    s += 4;
                                    op->type = OP_ELSE;
                                    i_top -= 1;
                                    goto lexer;
                                }
                                else if(strncmp(s, "elsif", 5) == 0 && !isword(s[5])){
                                    s += 5;
                                    op->type = OP_ELIF;
                                    i_top -= 1;
                                    goto lexer;
                                }
                                else{
                                    f_flatten_op_list(op, OP_IF);
                                    i_top -= 1;
                                    stack[i_top-1].type = T_ATOM;
                                    cur.type = T_Semi;
                                    cur.value.n = 0;
                                    goto try_reduce;
                                }
                            }
                            else if(stack[i_top-2].value.op->type == OP_while){
                                op_goto = get_op();
                                op_goto->type = OP_GOTO;
                                op_goto->right.op = NULL;
                                op_goto->right.n = 1;
                                op_break = get_op();
                                op_break->type = OP_GOTO;
                                op_break->right.op = NULL;
                                op_break->right.n = 5;
                                op_cond = f_new_op(OP_IF_NO, stack[i_top-1].value.op, op_break);
                                op_list = get_op_list(5);
                                op_list[1] = *(op_cond);
                                op_list[2] = *(cur.value.op);
                                op_list[4] = *(op_goto);
                                op = get_op();
                                op->type = OP_block;
                                op->left.n = 5;
                                op->right.op = op_list;
                                cv = CV_close(op);
                                op_cv = get_op();
                                op_cv->type = OP_CV;
                                op_cv->right.op = NULL;
                                op_cv->right.cv = cv;
                                stack[i_top-2].value.op = op_cv;
                                i_top -= 1;
                                stack[i_top-1].type = T_ATOM;
                                cur.type = T_Semi;
                                cur.value.n = 0;
                                goto try_reduce;
                            }
                            else if(stack[i_top-2].value.op->type == OP_for){
                                if(stack[i_top-1].value.op->type == OP_SEQ){
                                    f_flatten_op_list(stack[i_top-1].value.op, OP_SEQ);
                                    if(stack[i_top-1].value.op->left.n != 3){
                                        puts("for condition");
                                        dump_parse_stack(stack, i_top, cur, s);
                                        exit(0);
                                    }
                                    op_init = stack[i_top-1].value.op->right.op;
                                    op_cond = op_init + 1;
                                    op_cont = op_init + 2;
                                }
                                else{
                                    puts("for cond");
                                    dump_parse_stack(stack, i_top, cur, s);
                                    exit(0);
                                }
                                op_goto = get_op();
                                op_goto->type = OP_GOTO;
                                op_goto->right.op = NULL;
                                op_goto->right.n = 1;
                                op_break = get_op();
                                op_break->type = OP_GOTO;
                                op_break->right.op = NULL;
                                op_break->right.n = 5;
                                op_cond = f_new_op(OP_IF_NO, op_cond, op_break);
                                op_list = get_op_list(5);
                                op_list[0] = *(op_init);
                                op_list[1] = *(op_cond);
                                op_list[2] = *(cur.value.op);
                                op_list[3] = *(op_cont);
                                op_list[4] = *(op_goto);
                                op = get_op();
                                op->type = OP_block;
                                op->left.n = 5;
                                op->right.op = op_list;
                                cv = CV_close(op);
                                op_cv = get_op();
                                op_cv->type = OP_CV;
                                op_cv->right.op = NULL;
                                op_cv->right.cv = cv;
                                stack[i_top-2].value.op = op_cv;
                                i_top -= 1;
                                stack[i_top-1].type = T_ATOM;
                                cur.type = T_Semi;
                                cur.value.n = 0;
                                goto try_reduce;
                            }
                            puts("cv2");
                            dump_parse_stack(stack, i_top, cur, s);
                            exit(0);
                        }
                        puts("unhandled block");
                        dump_parse_stack(stack, i_top, cur, s);
                        exit(0);
                    }
                    memcpy(stack + i_top - 2, stack + i_top - 1, sizeof(struct TOK));
                    i_top -= 1;
                    goto lexer;
                }
            }
            else{
                puts("Don't know reduce_postfix");
                dump_parse_stack(stack, i_top, cur, s);
                exit(0);
            }
        }
        if(!cur.type){
            goto lexer;
        }
        else if(cur.type == T_EOF){
            break;
        }
        do_shift:
        if(cur.type == T_ATOM){
            if(stack[i_top-1].type == T_ATOM){
                if((stack[i_top-2].type == T_FN_LIST && (stack[i_top-2].value.n == WORD_print || stack[i_top-2].value.n == WORD_printf)) || (stack[i_top-2].type == T_BOC && stack[i_top-3].type == T_FN_LIST && (stack[i_top-3].value.n == WORD_print || stack[i_top-3].value.n == WORD_printf))){
                    stack[i_top-0].type = T_Comma;
                    i_top++;
                    goto try_reduce;
                }
                puts("unexpected atom");
                dump_parse_stack(stack, i_top, cur, s);
                exit(0);
            }
        }
        else if(cur.type == T_BOC){
            if(cur.value.n == '{'){
                tb_cv = 1;
                if(stack[i_top-1].type == T_ATOM){
                    tn_type = stack[i_top-1].value.op->type;
                    if(tn_type==OP_SIGIL ||tn_type==OP_LOCAL ||tn_type==OP_GLOBAL ){
                        tb_cv = 0;
                    }
                }
                if(tb_cv){
                    CV_begin();
                    if(stack[i_top-1].type == T_BOS && stack[i_top-1].value.op->type == OP_SUB){
                        cv_cur->flag = CVf_sub;
                    }
                }
            }
        }
        stack[i_top++] = cur;
    }
    return i_top;
}

struct SV* eval_op(struct OP* op, int tn_context, int tn_level){
    struct SV* sv;
    struct SV* sv_ret;
    struct SV* sv_a;
    int tn_word;
    struct SV* sv_right;
    struct AV* av;
    char* s;
    int tn_size;
    char* s2;
    struct SV* sv_io;
    struct SV* sv_file;
    char* ts_mode;
    char* s_end;
    FILE* file_tmp;
    FILE* file_in;
    int n;
    int i_var;
    struct SV* sv_var;
    struct HV* hv;
    struct SV* sv_b;
    struct SV* sv_key;
    int i;
    struct AV* av_a;
    struct AV* av_b;
    struct SV* sv_name;
    int i_sub;
    struct CV* cv;
    struct SV* sv_arg;
    int i_file_scope_save;
    int n_save;
    struct SV* sv_local;
    struct SV* sv_save;
    struct AV* av_arg;
    struct AV* av_save;
    struct AV* av_ret;
    struct OP* op_list;
    int i_else;
    struct SV* sv_cond;
    int tn_bool;
    struct SV* sv_sep;
    struct SV* sv_1st;
    struct SV* sv_pat;
    pcre* Re;
    const char* ts_err;
    int tn_where;
    int tn_option;
    struct SV* sv_re;
    struct SV* sv_s_a;
    struct SV* sv_s_b;
    int tn_ret;
    double f1;
    double f2;
    int8_t n1;
    int16_t n2;
    char* s_a;
    int n_a;

    if(!op){
        return NULL;
    }
    if(n_debug){
        int i;
        for(i=0; i<tn_level; i++){
            fputs("  ", stdout);
        }
        printf("eval: %s\n", get_OP_name(op->type));
    }
    switch(op->type){
        case OP_NOOP:
            return NULL;
        case OP_SEQ:
            eval_op(op->left.op, 0, tn_level);
            return eval_op(op->right.op, 0, tn_level);
        case OP_CV:
            return run_cv(op->right.cv, tn_context, tn_level + 1);
        case OP_CONST:
            return SV_copy(NULL, op->right.sv);
        case OP_LIST:
            return eval_list(op->left.op, op->right.op, tn_context, tn_level + 1);
        case OP_GOTO:
            sv = get_svreg(SVt_goto);
            sv->type = SVt_goto;
            sv->value.G.cv = op->left.cv;
            sv->value.G.i = op->right.n;
            return sv;
        case OP_GOTO_LABEL:
            fprintf(stderr, "goto label not supported\n");
            exit(-1);
        case OP_or:
            sv_ret = eval_op(op->left.op, 1, tn_level + 1);
            if(do_bool(sv_ret)){
                return sv_ret;
            }
            else{
                if(sv_ret && (sv_ret->flag & 3) == SVf_register){
                    SV_refdec(sv_ret);
                    sv_ret->flag = 0;
                    n_svreg--;
                }
                return eval_op(op->right.op, 1, tn_level + 1);
            }
        case OP_and:
            sv_ret = eval_op(op->left.op, 1, tn_level + 1);
            if(!do_bool(sv_ret)){
                return sv_ret;
            }
            else{
                if(sv_ret && (sv_ret->flag & 3) == SVf_register){
                    SV_refdec(sv_ret);
                    sv_ret->flag = 0;
                    n_svreg--;
                }
                return eval_op(op->right.op, 1, tn_level + 1);
            }
        case OP_UMINUS:
            sv_a = eval_op(op->right.op, 1, tn_level + 1);
            SV_to_int(sv_a);
            sv_a->value.n = -sv_a->value.n;
            return sv_a;
        case OP_NOT:
            sv_a = eval_op(op->right.op, 1, tn_level + 1);
            if(do_bool(sv_a)){
                sv_ret = sv_FALSE;
            }
            else{
                sv_ret = sv_TRUE;
            }
            if(sv_a && (sv_a->flag & 3) == SVf_register){
                SV_refdec(sv_a);
                sv_a->flag = 0;
                n_svreg--;
            }
            return sv_ret;
        case OP_UNARY:
            tn_word = op->left.n;
            if(tn_word < WORD_FN_LIST){
                sv_right = eval_list(NULL, op->right.op, 2, tn_level + 1);
                av = (struct AV*)sv_right->value.p;
            }
            else{
                sv_right = eval_op(op->right.op, 1, tn_level + 1);
            }
            sv_ret = NULL;
            switch(tn_word){
                case WORD_lc:
                    sv_ret = do_string(sv_right);
                    if(sv_ret){
                        int i;
                        s = sv_ret->value.S.s;
                        for(i=0; i<sv_ret->value.S.n; i++){
                            if(s[i] >= 'A' && s[i] <= 'Z'){
                                s[i] |= 0x60;
                            }
                        }
                    }
                    break;
                case WORD_uc:
                    sv_ret = do_string(sv_right);
                    if(sv_ret){
                        int i;
                        s = sv_ret->value.S.s;
                        for(i=0; i<sv_ret->value.S.n; i++){
                            if(s[i] >= 'a' && s[i] <= 'z'){
                                s[i] &= 0x3f;
                            }
                        }
                    }
                    break;
                case WORD_lcfirst:
                    sv_ret = do_string(sv_right);
                    if(sv_ret){
                        s = sv_ret->value.S.s;
                        if(sv_ret->value.S.n > 0){
                            if(s[0] >= 'A' && s[0] <= 'Z'){
                                s[0] |= 0x60;
                            }
                        }
                    }
                    break;
                case WORD_ucfirst:
                    sv_ret = do_string(sv_right);
                    if(sv_ret){
                        s = sv_ret->value.S.s;
                        if(sv_ret->value.S.n > 0){
                            if(s[0] >= 'a' && s[0] <= 'z'){
                                s[0] &= 0x3f;
                            }
                        }
                    }
                    break;
                case WORD_quotemeta:
                    sv_ret = do_string(sv_right);
                    if(sv_ret){
                        char* d;
                        int i;
                        s = sv_ret->value.S.s;
                        tn_size = sv_ret->value.S.n * 2;
                        s2=(char*)malloc(tn_size*sizeof(char));
                        d = s2;
                        for(i=0; i<sv_ret->value.S.n; i++){
                            if(!isword(s[i])){
                                *d++ = '\\';
                            }
                            *d++ = s[i];
                        }
                        free(sv_ret->value.S.s);
                        sv_ret->value.S.n = (int)(d - s2);
                        sv_ret->value.S.size = tn_size;
                    }
                    break;
                case WORD_print:
                case WORD_printf:
                    sv_io = AV_get(av, 0);
                    if(sv_io->type != SVt_io){
                        sv_io = &g_global[I_STDOUT];
                    }
                    else{
                        AV_shift(av);
                    }
                    if(tn_word == WORD_print){
                        do_print(sv_io, av);
                    }
                    else{
                        do_printf(sv_io, av);
                    }
                    if(sv_io && (sv_io->flag & 3) == SVf_register){
                        SV_refdec(sv_io);
                        sv_io->flag = 0;
                        n_svreg--;
                    }
                    break;
                case WORD_warn:
                case WORD_die:
                    sv_io = &g_global[I_STDERR];
                    do_print(sv_io, av);
                    if(tn_word == WORD_die){
                        exit(-1);
                    }
                    break;
                case WORD_open:
                    sv_io = AV_shift(av);
                    sv_file = AV_get(av, 0);
                    if(!(sv_io->type == SVt_io)){
                        puts("assert error: ! (sv_io->type==SVt_io)");
                        exit(0);
                    }
                    SV_refdec(sv_io);
                    if(sv_file && sv_file->type == SVt_string){
                        ts_mode = "r";
                        s = sv_file->value.S.s;
                        s_end = s + sv_file->value.S.n - 1;
                        while(*s_end == ' '){
                            s_end--;
                        }
                        if(*s_end == '|'){
                            ts_mode = NULL;
                        }
                        while(*s_end == ' '){
                            s_end--;
                        }
                        s_end[1] = '\0';
                        if(ts_mode){
                            while(*s == ' '){
                                s++;
                            }
                            if(*s == '<'){
                                ts_mode = "r";
                                s++;
                            }
                            else if(*s == '>'){
                                ts_mode = "w";
                                s++;
                            }
                            else if(*s == '|'){
                                ts_mode = NULL;
                                s++;
                            }
                            while(*s == ' '){
                                s++;
                            }
                        }
                        if(ts_mode){
                            file_tmp = fopen(s, ts_mode);
                            if(file_tmp){
                                sv_io->value.p = file_tmp;
                                SV_refinc(sv_io);
                                sv_ret = sv_io;
                            }
                            else{
                                sv_io->value.p = NULL;
                            }
                        }
                        else{
                            fprintf(stderr, "open: pipe yet to be supported\n");
                            exit(-1);
                        }
                    }
                    else{
                        fprintf(stderr, "open: missing file\n");
                        exit(-1);
                    }
                    break;
                case WORD_close:
                    SV_refdec(sv_right);
                    break;
                case WORD_fread:
                    sv_io = sv_right;
                    file_in = sv_io->value.p;
                    if(file_in){
                        s = fgets(s_line_buffer, 10000, file_in);
                        if(!s){
                            break;
                        }
                        else{
                            n = strlen(s);
                            sv_ret = get_svreg(SVt_string);
                            sv_ret->type = SVt_string;
                            sv_ret->refcnt = 1;
                            memset(&sv_ret->value, 0, sizeof(sv_ret->value));
                            sv_ret->value.S.s = s;
                            sv_ret->value.S.n = n;
                            sv_ret->value.S.size = 0;
                        }
                    }
                    break;
                default:
                    fprintf(stderr, "unsupported UNARY op [%s]\n", get_WORD_name(tn_word));
                    exit(-1);
            }
            if(sv_right && (sv_right->flag & 3) == SVf_register){
                SV_refdec(sv_right);
                sv_right->flag = 0;
                n_svreg--;
            }
            return sv_ret;
        case OP_MY:
        case OP_LOCAL:
            i_var = (int)op->right.n;
            sv_var = &g_local[i_var];
            if(op->type == OP_MY){
                if(op->left.n == '@'){
                    sv_var->type = SVt_av;
                }
                else if(op->left.n == '%'){
                    sv_var->type = SVt_hv;
                }
                else if(op->left.n == '*'){
                    sv_var->type = SVt_io;
                }
                else{
                    sv_var->type = SVt_undef;
                }
            }
            if(tn_context == 3){
                return sv_var;
            }
            else if(tn_context == 0){
                return NULL;
            }
            else{
                return SV_copy(NULL, sv_var);
            }
        case OP_GLOBAL:
            i_var = (int)op->right.n;
            sv_var = &g_global[i_var];
            if(tn_context == 3){
                return sv_var;
            }
            else if(tn_context == 0){
                return NULL;
            }
            else{
                return SV_copy(NULL, sv_var);
            }
        case OP_HASH_INDEX:
            sv_a = eval_op(op->left.op, 1, tn_level + 1);
            if(sv_a->type == SVt_hv){
                hv = (struct HV*)sv_a->value.p;
            }
            else{
                fprintf(stderr, "non-hash index\n");
                exit(-1);
            }
            sv_b = eval_op(op->right.op, 1, tn_level + 1);
            sv_key = do_string(sv_b);
            if(sv_key && sv_key->type == SVt_string){
                sv = HV_get(hv, sv_key->value.S.s, sv_key->value.S.n);
                if(sv == NULL && tn_context == 3){
                    sv = get_sv(0);
                    HV_set(hv, sv_key->value.S.s, sv_key->value.S.n, sv);
                }
            }
            if(sv_a && (sv_a->flag & 3) == SVf_register){
                SV_refdec(sv_a);
                sv_a->flag = 0;
                n_svreg--;
            }
            if(sv_b && (sv_b->flag & 3) == SVf_register){
                SV_refdec(sv_b);
                sv_b->flag = 0;
                n_svreg--;
            }
            if(sv_key && (sv_key->flag & 3) == SVf_register){
                SV_refdec(sv_key);
                sv_key->flag = 0;
                n_svreg--;
            }
            return sv;
        case OP_ARRAY_INDEX:
            sv_a = eval_op(op->left.op, 1, tn_level + 1);
            if(sv_a->type == SVt_av){
                av = (struct AV*)sv_a->value.p;
            }
            else{
                fprintf(stderr, "non-array index\n");
                exit(-1);
            }
            sv_b = eval_op(op->left.op, 1, tn_level + 1);
            i = do_int(sv_b);
            sv = AV_get(av, i);
            if(sv == NULL && tn_context == 3){
                sv = get_sv(0);
                AV_set(av, i, sv);
            }
            if(sv_a && (sv_a->flag & 3) == SVf_register){
                SV_refdec(sv_a);
                sv_a->flag = 0;
                n_svreg--;
            }
            if(sv_b && (sv_b->flag & 3) == SVf_register){
                SV_refdec(sv_b);
                sv_b->flag = 0;
                n_svreg--;
            }
            return sv;
        case OP_ASSIGN:
            sv_var = eval_op(op->left.op, 3, tn_level + 1);
            if(sv_var->type == SVt_av && (sv_var->flag & 3) == SVf_register){
                sv_b = eval_op(op->right.op, 2, tn_level + 1);
                av_a = (struct AV*)sv_var->value.p;
                if(!av_a){
                    av_a = AV_new();
                    sv_a->value.p = av_a;
                }
                if(sv_b->type == SVt_av){
                    int i;
                    av_b = (struct AV*)sv_b->value.p;
                    for(i=av_a->i_0; i<av_a->i_n; i++){
                        do_assign(av_a->p_array[i], AV_get(av_b, i - av_a->i_0));
                    }
                }
                else{
                    int i;
                    for(i=av_a->i_0; i<av_a->i_n; i++){
                        if(i == 0){
                            do_assign(av_a->p_array[i], sv_b);
                        }
                        else{
                            SV_undef(av_a->p_array[i]);
                        }
                    }
                }
            }
            else{
                sv_b = eval_op(op->right.op, 1, tn_level + 1);
                do_assign(sv_var, sv_b);
            }
            sv_ret = SV_copy(NULL, sv_var);
            if(sv_var && (sv_var->flag & 3) == SVf_register){
                SV_refdec(sv_var);
                sv_var->flag = 0;
                n_svreg--;
            }
            if(sv_b && (sv_b->flag & 3) == SVf_register){
                SV_refdec(sv_b);
                sv_b->flag = 0;
                n_svreg--;
            }
            return sv_ret;
        case OP_Fcall:
            sv_name = op->left.sv;
            sv_name->value.S.s[sv_name->value.S.n] = '\0';
            i_sub = find_global(sv_name->value.S.s);
            if(i_sub){
                cv = subs[i_sub];
                sv_arg = eval_op(op->right.op, 2, tn_level + 1);
                i_file_scope_save = -1;
                if(cv->i_file != cur_file_scope){
                    i_file_scope_save = cur_file_scope;
                    cur_file_scope = cv->i_file;
                    g_local = g_file_scopes[cur_file_scope].sv_local;
                    g_local_len = g_file_scopes[cur_file_scope].n;
                    g_local_size = g_file_scopes[cur_file_scope].n_size;
                }
                n_save = 0;
                if(cv->i_start + cv->n_vars > g_local_len){
                    n_save = g_local_len - cv->i_start;
                }
                else{
                    n_save = cv->n_vars;
                }
                if(n_save > 0){
                    sv_local = g_local + cv->i_start;
                    sv_save=(struct SV*)malloc(n_save*sizeof(struct SV));
                    memcpy(sv_save, sv_local, n_save * sizeof(struct SV));
                }
                n_save = 0;
                if(cv->i_start + cv->n_vars > g_local_len){
                    n_save = g_local_len - cv->i_start;
                }
                else{
                    n_save = cv->n_vars;
                }
                if(n_save > 0){
                    sv_local = g_local + cv->i_start;
                    sv_save=(struct SV*)malloc(n_save*sizeof(struct SV));
                    memcpy(sv_save, sv_local, n_save * sizeof(struct SV));
                }
                if(!sv_arg){
                    av_arg = NULL;
                }
                else if(sv_arg->type == SVt_av){
                    av_arg = (struct AV*)sv_arg->value.p;
                    sv_arg->type = 0;
                    if(sv_arg && (sv_arg->flag & 3) == SVf_register){
                        sv_arg->flag = 0;
                        n_svreg--;
                    }
                }
                else{
                    av_arg = AV_new();
                    AV_push(av_arg, sv_arg);
                    if(sv_arg && (sv_arg->flag & 3) == SVf_register){
                        sv_arg->flag = 0;
                        n_svreg--;
                    }
                }
                av_save = g_global[I_at_ARG].value.p;
                g_global[I_at_ARG].value.p = av_arg;
                sv_ret = run_cv(cv, tn_context, tn_level + 1);
                if(sv_ret && (sv_ret->flag & 3) == SVf_register){
                    SV_refdec(sv_ret);
                    sv_ret->flag = 0;
                    n_svreg--;
                }
                av_ret = (struct AV*)g_global[I_at_ARG].value.p;
                if(av_ret == av_arg && av_arg){
                    AV_free(av_arg);
                    av_ret = NULL;
                }
                if(av_ret){
                    if(tn_context == 2){
                        sv_ret = get_svreg(SVt_av);
                        sv_ret->value.p = (void*)av_ret;
                    }
                    else{
                        sv_ret = AV_shift(av_ret);
                        SV_refinc(sv_ret);
                        AV_free(av);
                    }
                }
                else{
                    sv_ret = NULL;
                }
                g_global[I_at_ARG].value.p = av_save;
                if(n_save){
                    memcpy(sv_local, sv_save, n_save * sizeof(struct SV));
                }
                if(n_save){
                    memcpy(sv_local, sv_save, n_save * sizeof(struct SV));
                }
                if(i_file_scope_save >= 0){
                    cur_file_scope = i_file_scope_save;
                    g_local = g_file_scopes[cur_file_scope].sv_local;
                    g_local_len = g_file_scopes[cur_file_scope].n;
                    g_local_size = g_file_scopes[cur_file_scope].n_size;
                }
                return sv_ret;
            }
            else{
                fprintf(stderr, "Undefined subroutine %s\n", sv_name->value.S.s);
                exit(-1);
            }
            return NULL;
        case OP_RETURN:
            av_ret = (struct AV*)g_global[I_at_ARG].value.p;
            if(av_ret){
                AV_free(av_ret);
            }
            sv_ret = eval_op(op->right.op, 2, tn_level + 1);
            if(!sv_ret){
                g_global[I_at_ARG].value.p = NULL;
            }
            else if(sv_ret->type == SVt_av){
                g_global[I_at_ARG].value.p = (struct AV*)sv_ret->value.p;
                if(sv_ret && (sv_ret->flag & 3) == SVf_register){
                    sv_ret->flag = 0;
                    n_svreg--;
                }
            }
            else{
                av_ret = AV_new();
                AV_push(av_ret, sv_ret);
                g_global[I_at_ARG].value.p = av_ret;
            }
            sv_ret = get_svreg(SVt_undef);
            cv = op->left.cv;
            sv_ret->type = SVt_goto;
            sv_ret->value.G.cv = cv;
            sv_ret->value.G.i = GOTO_return;
            return sv_ret;
        case OP_IF:
            n = op->left.n;
            op_list = op->right.op;
            i_else = 0;
            if(n % 2 == 1){
                i_else = n - 1;
                n--;
            }
            for(i=0; i<n; i+=2){
                sv_cond = eval_op(&op_list[i], 1, tn_level + 1);
                tn_bool = do_bool(sv_cond);
                if(sv_cond && (sv_cond->flag & 3) == SVf_register){
                    SV_refdec(sv_cond);
                    sv_cond->flag = 0;
                    n_svreg--;
                }
                if(tn_bool){
                    return eval_op(&op_list[i+1], 0, tn_level + 1);
                }
            }
            if(i_else){
                return eval_op(&op_list[i_else], 0, tn_level + 1);
            }
            return NULL;
        case OP_IF_YES:
            sv_cond = eval_op(op->left.op, 1, tn_level + 1);
            tn_bool = do_bool(sv_cond);
            if(sv_cond && (sv_cond->flag & 3) == SVf_register){
                SV_refdec(sv_cond);
                sv_cond->flag = 0;
                n_svreg--;
            }
            if(tn_bool){
                return eval_op(op->right.op, 0, tn_level + 1);
            }
            return NULL;
        case OP_IF_NO:
            sv_cond = eval_op(op->left.op, 1, tn_level + 1);
            tn_bool = do_bool(sv_cond);
            if(sv_cond && (sv_cond->flag & 3) == SVf_register){
                SV_refdec(sv_cond);
                sv_cond->flag = 0;
                n_svreg--;
            }
            if(!tn_bool){
                return eval_op(op->right.op, 0, tn_level + 1);
            }
            return NULL;
        case OP_join:
            sv_b = eval_list(NULL, op->right.op, tn_context, tn_level + 1);
            av = (struct AV*)sv_b->value.p;
            sv_sep = AV_shift(av);
            sv_1st = AV_shift(av);
            sv = do_string(sv_1st);
            for(i=av->i_0; i<av->i_n; i++){
                SV_append_sv(sv, sv_sep);
                SV_append_sv(sv, av->p_array[i]);
            }
            if(sv_1st && (sv_1st->flag & 3) == SVf_register){
                SV_refdec(sv_1st);
                sv_1st->flag = 0;
                n_svreg--;
            }
            if(sv_b && (sv_b->flag & 3) == SVf_register){
                SV_refdec(sv_b);
                sv_b->flag = 0;
                n_svreg--;
            }
            if(sv_sep && (sv_sep->flag & 3) == SVf_register){
                SV_refdec(sv_sep);
                sv_sep->flag = 0;
                n_svreg--;
            }
            return sv;
        case OP_ReMatch:
            sv_ret = NULL;
            sv_a = eval_op(op->left.op, 1, tn_level + 1);
            if(sv_a && sv_a->type == SVt_string && sv_a->value.S.n > 0){
                if(op->right.op->type == OP_ReC){
                    sv_pat = op->right.op->right.sv;
                }
                else if(op->right.op->type == OP_Re){
                    sv_pat = eval_op(op->right.op, 1, tn_level + 1);
                }
                if(sv_pat && sv_pat->value.p){
                    Re = sv_pat->value.p;
                }
                else{
                    fprintf(stderr, "error: ReMatch\n");
                    exit(-1);
                }
                s_regex_str = sv_a->value.S.s;
                n_regex_len = sv_a->value.S.n;
                n_regex_caps = pcre_exec(Re, NULL, s_regex_str, n_regex_len, sv_a->value.S.pos, 0, regex_offs, 30);
                if(n_regex_caps < 0){
                    n_regex_caps = 0;
                }
                else if(n_regex_caps == 0){
                    n_regex_caps = 10;
                }
                if(n_regex_caps){
                    if(tn_context == 2){
                        int i;
                        sv_ret = get_svreg(SVt_av);
                        av = AV_new();
                        sv_ret->type = SVt_av;
                        sv_ret->value.p = (void*)av;
                        for(i=1; i<n_regex_caps; i++){
                            sv = g_global + I_MATCH + i;
                            s = s_regex_str + regex_offs[i*2];
                            n = regex_offs[i*2+1] - regex_offs[i*2];
                            sv->type = SVt_string;
                            sv->refcnt = 1;
                            memset(&sv->value, 0, sizeof(sv->value));
                            sv->value.S.s = s;
                            sv->value.S.n = n;
                            AV_push(av, sv);
                        }
                    }
                    else{
                        sv_ret = get_svreg(SVt_int);
                        sv_ret->value.n = n_regex_caps;
                    }
                }
                else{
                    sv_ret = NULL;
                }
            }
            return sv_ret;
        case OP_ReC:
            return op->right.sv;
        case OP_Re:
            sv_pat = eval_op(op->right.op, 1, tn_level + 1);
            if(!(sv_pat->type == SVt_string)){
                puts("assert error: ! (sv_pat->type == SVt_string)");
                exit(0);
            }
            sv_pat->value.S.s[sv_pat->value.S.n] = '\0';
            tn_option = 0;
            Re = pcre_compile(sv_pat->value.S.s, tn_option, &ts_err, &tn_where, NULL);
            if(!Re){
                fprintf(stderr, "Regex Pattern error: %s\n", ts_err);
                exit(-1);
            }
            if(op->right.op->type == OP_CONST){
                sv_re = get_sv(SVt_regex);
                op->type = OP_ReC;
                op->right.sv = sv_re;
            }
            else{
                sv_re = get_svreg(SVt_regex);
            }
            sv_re->value.p = Re;
            if(sv_pat && (sv_pat->flag & 3) == SVf_register){
                SV_refdec(sv_pat);
                sv_pat->flag = 0;
                n_svreg--;
            }
            return sv_re;
        case OP_VarMatch:
            i = op->right.n;
            if(n_regex_caps == 0 || i >= n_regex_caps){
                return NULL;
            }
            if(i == -1){
                sv_ret = &g_global[I_PREMATCH];
                sv_ret->type = SVt_string;
                sv_ret->refcnt = 1;
                memset(&sv_ret->value, 0, sizeof(sv_ret->value));
                sv_ret->value.S.s = s_regex_str;
                sv_ret->value.S.n = regex_offs[0];
            }
            else if(i == -2){
                sv_ret = &g_global[I_POSTMATCH];
                s = s_regex_str + regex_offs[1];
                n = n_regex_len - regex_offs[1];
                sv_ret->type = SVt_string;
                sv_ret->refcnt = 1;
                memset(&sv_ret->value, 0, sizeof(sv_ret->value));
                sv_ret->value.S.s = s;
                sv_ret->value.S.n = n;
            }
            else{
                sv_ret = g_global + I_MATCH + i;
                s = s_regex_str + regex_offs[i*2];
                n = regex_offs[i*2+1] - regex_offs[i*2];
                sv_ret->type = SVt_string;
                sv_ret->refcnt = 1;
                memset(&sv_ret->value, 0, sizeof(sv_ret->value));
                sv_ret->value.S.s = s;
                sv_ret->value.S.n = n;
            }
            return sv_ret;
        case OP_INC:
        case OP_DEC:
            sv_var = eval_op(op->right.op, 3, tn_level + 1);
            sv_ret = SV_copy(NULL, sv_var);
            SV_to_int(sv_var);
            if(op->type == OP_INC){
                sv_var->value.n++;
            }
            else{
                sv_var->value.n--;
            }
            return sv_ret;
        default:
            if(op->type & 0x1){
                sv_a = eval_op(op->left.op, 1, tn_level + 1);
                sv_b = eval_op(op->right.op, 1, tn_level + 1);
                sv = NULL;
                if(op->type & 0x4){
                    if(op->type & 0x40){
                        sv_s_a = do_string(sv_a);
                        sv_s_b = do_string(sv_b);
                        if(!sv_s_a && !sv_s_b){
                            tn_ret = 0;
                        }
                        else if(!sv_s_a){
                            tn_ret = -1;
                        }
                        else if(!sv_s_b){
                            tn_ret = 1;
                        }
                        else{
                            n = sv_s_a->value.S.n;
                            if(n < sv_s_b->value.S.n){
                                n = sv_s_b->value.S.n;
                            }
                            tn_ret = strncmp(sv_s_a->value.S.s, sv_s_b->value.S.s, n);
                        }
                        if(sv_s_a && (sv_s_a->flag & 3) == SVf_register){
                            SV_refdec(sv_s_a);
                            sv_s_a->flag = 0;
                            n_svreg--;
                        }
                        if(sv_s_b && (sv_s_b->flag & 3) == SVf_register){
                            SV_refdec(sv_s_b);
                            sv_s_b->flag = 0;
                            n_svreg--;
                        }
                        switch (op->type){
                            case OP_eq:
                                sv = tn_ret == 0 ? sv_TRUE: sv_FALSE;
                                break;
                            case OP_ne:
                                sv = tn_ret != 0 ? sv_TRUE: sv_FALSE;
                                break;
                            case OP_lt:
                                sv = tn_ret < 0 ? sv_TRUE: sv_FALSE;
                                break;
                            case OP_gt:
                                sv = tn_ret > 0 ? sv_TRUE: sv_FALSE;
                                break;
                            case OP_le:
                                sv = tn_ret <= 0 ? sv_TRUE: sv_FALSE;
                                break;
                            case OP_ge:
                                sv = tn_ret >= 0 ? sv_TRUE: sv_FALSE;
                                break;
                            case OP_cmp:
                                sv = get_svreg(SVt_undef);
                                sv->type = SVt_int;
                                sv->value.n = tn_ret;
                        }
                    }
                    else if(op->type & 0x10){
                        if(sv_a->type == SVt_float || sv_b->type == SVt_float){
                            f1 = do_float(sv_a);
                            f2 = do_float(sv_b);
                            switch(op->type){
                                case OP_EqEq:
                                    sv = f1 == f2 ? sv_TRUE: sv_FALSE;
                                    break;
                                case OP_EmarkEq:
                                    sv = f1 != f2 ? sv_TRUE: sv_FALSE;
                                    break;
                                case OP_Lt:
                                    sv = f1 < f2 ? sv_TRUE: sv_FALSE;
                                    break;
                                case OP_Gt:
                                    sv = f1 > f2 ? sv_TRUE: sv_FALSE;
                                    break;
                                case OP_LtEq:
                                    sv = f1 <= f2 ? sv_TRUE: sv_FALSE;
                                    break;
                                case OP_GtEq:
                                    sv = f1 >= f2 ? sv_TRUE: sv_FALSE;
                                    break;
                                case OP_LtEqGt:
                                    sv = get_svreg(SVt_undef);
                                    if(f1 == f2){
                                        sv->type = SVt_int;
                                        sv->value.n = 0;
                                    }
                                    else if(f1 < f2){
                                        sv->type = SVt_int;
                                        sv->value.n = -1;
                                    }
                                    else{
                                        sv->type = SVt_int;
                                        sv->value.n = 1;
                                    }
                            }
                        }
                        else{
                            n1 = do_int(sv_a);
                            n2 = do_int(sv_b);
                            switch(op->type){
                                case OP_EqEq:
                                    sv = n1 == n2 ? sv_TRUE: sv_FALSE;
                                    break;
                                case OP_EmarkEq:
                                    sv = n1 != n2 ? sv_TRUE: sv_FALSE;
                                    break;
                                case OP_Lt:
                                    sv = n1 < n2 ? sv_TRUE: sv_FALSE;
                                    break;
                                case OP_Gt:
                                    sv = n1 > n2 ? sv_TRUE: sv_FALSE;
                                    break;
                                case OP_LtEq:
                                    sv = n1 <= n2 ? sv_TRUE: sv_FALSE;
                                    break;
                                case OP_GtEq:
                                    sv = n1 >= n2 ? sv_TRUE: sv_FALSE;
                                    break;
                                case OP_LtEqGt:
                                    sv = get_svreg(SVt_undef);
                                    if(n1 == n2){
                                        sv->type = SVt_int;
                                        sv->value.n = 0;
                                    }
                                    else if(n1 < n2){
                                        sv->type = SVt_int;
                                        sv->value.n = -1;
                                    }
                                    else{
                                        sv->type = SVt_int;
                                        sv->value.n = 1;
                                    }
                            }
                        }
                    }
                }
                else{
                    if(op->type & 0x40){
                        if(op->type == OP_Dot){
                            if(!((sv_a->flag & 3) == SVf_register)){
                                puts("assert error: ! ((sv_a->flag&3)==SVf_register)");
                                exit(0);
                            }
                            if(sv_a->type == SVt_string){
                                sv = sv_a;
                                sv_a = NULL;
                            }
                            else{
                                sv = do_string(sv_a);
                            }
                            SV_string_on_write(sv);
                            SV_append_sv(sv, sv_b);
                        }
                        else if(op->type == OP_x){
                            int i;
                            sv = get_svreg(SVt_string);
                            n = do_int(sv_b);
                            if(sv_a->type != SVt_string){
                                sv_s_a = do_string(sv_a);
                                if(sv_a && (sv_a->flag & 3) == SVf_register){
                                    SV_refdec(sv_a);
                                    sv_a->flag = 0;
                                    n_svreg--;
                                }
                                sv_a = sv_s_a;
                            }
                            s_a = sv_a->value.S.s;
                            n_a = sv_a->value.S.n;
                            sv->value.S.n = n_a * n;
                            SV_resize(sv, sv->value.S.n + 20);
                            s = sv->value.S.s;
                            for(i=0; i<n; i++){
                                memcpy(s, s_a, n_a);
                                s += n_a;
                            }
                        }
                    }
                    else if(op->type & 0x10){
                        if(sv_a->type == SVt_float || sv_b->type == SVt_float || op->type == OP_Div){
                            f1 = do_float(sv_a);
                            f2 = do_float(sv_b);
                            if(op->type == OP_Plus){
                                f1 += f2;
                            }
                            else if(op->type == OP_Minus){
                                f1 -= f2;
                            }
                            else if(op->type == OP_Mult){
                                f1 *= f2;
                            }
                            else if(op->type == OP_Div){
                                f1 /= f2;
                            }
                            else if(op->type == OP_MultMult){
                                f1 = pow(f1, f2);
                            }
                            sv = get_svreg(SVt_undef);
                            sv->type = SVt_float;
                            sv->value.f = f1;
                            goto done_bin;
                        }
                        if(1){
                            n1 = do_int(sv_a);
                            n2 = do_int(sv_b);
                            if(op->type == OP_Plus){
                                n1 += n2;
                            }
                            else if(op->type == OP_Minus){
                                n1 -= n2;
                            }
                            else if(op->type == OP_Mult){
                                n1 *= n2;
                            }
                            else if(op->type == OP_Div){
                                n1 /= n2;
                            }
                            else if(op->type == OP_Mod){
                                n1 %= n2;
                            }
                            else if(op->type == OP_Or){
                                n1 |= n2;
                            }
                            else if(op->type == OP_And){
                                n1 &= n2;
                            }
                            else if(op->type == OP_Ctrl){
                                n1 ^= n2;
                            }
                            else if(op->type == OP_GtGt){
                                n1 >>= n2;
                            }
                            else if(op->type == OP_LtLt){
                                n1 <<= n2;
                            }
                            sv = get_svreg(SVt_undef);
                            sv->type = SVt_int;
                            sv->value.n = n1;
                            goto done_bin;
                        }
                    }
                }
                done_bin:
                if(sv_a && (sv_a->flag & 3) == SVf_register){
                    SV_refdec(sv_a);
                    sv_a->flag = 0;
                    n_svreg--;
                }
                if(sv_b && (sv_b->flag & 3) == SVf_register){
                    SV_refdec(sv_b);
                    sv_b->flag = 0;
                    n_svreg--;
                }
                if(!sv){
                    fprintf(stderr, "unhandled bin op\n");
                    exit(-1);
                }
                return sv;
            }
            else if(op->type & 0x2){
                sv_a = eval_op(op->left.op, 3, tn_level + 1);
                sv_b = eval_op(op->right.op, 1, tn_level + 1);
                if(op->type & 0x40){
                    SV_to_string(sv_a);
                    SV_string_on_write(sv_a);
                    if(op->type == OP_DotEq){
                        SV_append_sv(sv_a, sv_b);
                    }
                }
                else if(op->type & 0x10){
                    if(sv_a->type == SVt_float || sv_b->type == SVt_float || op->type == OP_DivEq){
                        f1 = do_float(sv_a);
                        f2 = do_float(sv_b);
                        if(op->type == OP_PlusEq){
                            f1 += f2;
                        }
                        else if(op->type == OP_MinusEq){
                            f1 -= f2;
                        }
                        else if(op->type == OP_MultEq){
                            f1 *= f2;
                        }
                        else if(op->type == OP_DivEq){
                            f1 /= f2;
                        }
                        SV_to_float(sv_a);
                        sv_a->type = SVt_float;
                        sv_a->value.f = f1;
                    }
                    if(1){
                        n1 = do_int(sv_a);
                        n2 = do_int(sv_b);
                        if(op->type == OP_PlusEq){
                            n1 += n2;
                        }
                        else if(op->type == OP_MinusEq){
                            n1 -= n2;
                        }
                        else if(op->type == OP_MultEq){
                            n1 *= n2;
                        }
                        else if(op->type == OP_DivEq){
                            n1 /= n2;
                        }
                        else if(op->type == OP_ModEq){
                            n1 %= n2;
                        }
                        else if(op->type == OP_OrEq){
                            n1 |= n2;
                        }
                        else if(op->type == OP_AndEq){
                            n1 &= n2;
                        }
                        else if(op->type == OP_CtrlEq){
                            n1 ^= n2;
                        }
                        else if(op->type == OP_GtGtEq){
                            n1 >>= n2;
                        }
                        else if(op->type == OP_LtLtEq){
                            n1 <<= n2;
                        }
                        SV_to_int(sv_a);
                        sv_a->type = SVt_int;
                        sv_a->value.n = n1;
                    }
                }
                done_opeq:
                sv_ret = SV_copy(NULL, sv_a);
                if(sv_a && (sv_a->flag & 3) == SVf_register){
                    SV_refdec(sv_a);
                    sv_a->flag = 0;
                    n_svreg--;
                }
                if(sv_b && (sv_b->flag & 3) == SVf_register){
                    SV_refdec(sv_b);
                    sv_b->flag = 0;
                    n_svreg--;
                }
                return sv_ret;
            }
            break;
    }
    fprintf(stderr, "unsupported op: %s\n", get_OP_name(op->type));
    exit(-1);
    return NULL;
}

void* do_string(struct SV* sv){
    struct SV* sv_r;

    if(!sv || sv->type == SVt_undef){
        return NULL;
    }
    if(sv->type == SVt_string){
        return SV_copy(NULL, sv);
    }
    sv_r = get_svreg(SVt_string);
    sv_r->value.S.s = NULL;
    sv_r->value.S.n = 0;
    sv_r->value.S.size = 0;
    if(sv->type == SVt_int){
        SV_append_i(sv_r, sv->value.n);
    }
    else if(sv->type == SVt_float){
        SV_append_f(sv_r, sv->value.f);
    }
    else{
        fprintf(stderr, "do_string type [%s] not supported\n", get_SV_name(sv->type));
        exit(-1);
    }
    return sv_r;
}

void SV_refdec(struct SV* sv){
    if(sv->refcnt > 0){
        sv->refcnt--;
        if(sv->refcnt == 0){
            if(sv->copy){
                int i;
                i = sv->copy;
                sv->copy = 0;
                if(!(svcopy[i] > 0)){
                    puts("assert error: ! (svcopy[i]>0)");
                    exit(0);
                }
                svcopy[i]--;
                if(svcopy[i] == 0){
                    n_svcopy--;
                }
                else{
                    return;
                }
            }
            else if(sv->type == SVt_string){
                if(sv->value.S.size > 0){
                    free(sv->value.S.s);
                }
            }
            else if(sv->value.p){
                if(sv->type == SVt_sv){
                    SV_refdec((struct SV*)sv->value.p);
                }
                else if(sv->type == SVt_av){
                    AV_free((struct AV*)sv->value.p);
                }
                else if(sv->type == SVt_hv){
                    HV_free((struct HV*)sv->value.p);
                }
                else if(sv->type == SVt_io){
                    fclose((FILE*)sv->value.p);
                }
                else if(sv->type == SVt_regex){
                    pcre_free(sv->value.p);
                }
                sv->value.p = NULL;
            }
        }
    }
    return ;
}

char* f_skip_spaces(char* s){
    while(1){
        if(!s || s >= s_src_end){
            s = f_load_src(NULL);
            if(s == NULL){
                return s;
            }
        }
        if(isspace(*s)){
            s++;
        }
        else if(*s == '#'){
            s = f_skip_line(s);
        }
        else{
            return s;
        }
    }
}

char* f_get_regex(char* s, struct OP ** p_op){
    char* s2;
    int n;
    struct OP* op_str;
    struct OP* op_re;

    s = f_scan_delim(s, &s2, &n);
    if(s && p_op){
        s2[n] = '\0';
        op_str = f_parse_str_qq(s2, 1);
        op_re = get_op();
        op_re->type = OP_Re;
        op_re->right.op = NULL;
        op_re->right.op = op_str;
        *p_op = op_re;
    }
    return s;
}

struct OP* get_op(){
    if(i_op_free >= n_op_free){
        op_freelist=(struct OP*)calloc(100, sizeof(struct OP));
        if(heap_len + 1 > heap_size){
            heap = f_darray_expand(heap, sizeof(struct T), &heap_size);
        }
        heap[heap_len].a1 = HEAP_op;
        heap[heap_len].a2 = 100;
        heap[heap_len].a3 = op_freelist;
        heap_len++;
        i_op_free = 0;
        n_op_free = 100;
    }
    return &op_freelist[i_op_free++];
}

char* f_get_number(char* s, struct SV* sv){
    double nv = 0.0;
    int uv = 0;
    int use_nv = 0;
    int tn_shift;
    unsigned char tc_digit;
    double pf_shift[5] = {1,2,4,8,16};
    char* ts_start;
    double tf_place;
    bool tb_sign;
    int tn_exp;

    tn_shift = 0;
    if(*s == '0'){
        if(s[1] == 'x'){
            s += 2;
            tn_shift = 4;
        }
        else if(s[1] == 'b'){
            s += 2;
            tn_shift = 1;
        }
        else if((s[1]=='.' || s[1]=='e' || s[1]=='E')){
        }
        else{
            s++;
            tn_shift = 3;
        }
    }
    if(tn_shift > 0){
        while(1){
            switch(*s){
                case '_': s++; break;
                case '8': case '9': 
                    if(tn_shift == 3){
                        puts("Illegal octal digit");
                        exit(0);
                    }
                case '2': case '3': case '4': case '5': case '6': case '7': 
                    if(tn_shift == 3){
                        puts("Illegal binary digit");
                        exit(0);
                    }
                case '0': case '1': 
                    tc_digit = *s & 0xf;
                    s++;
                    break;
                case 'a': case 'b': case 'c': case 'd': case 'e': case 'f': case 'A': case 'B': case 'C': case 'D': case 'E': case 'F': 
                    if(tn_shift != 4){
                        goto out;
                    }
                    tc_digit = *s & 7 + 9;
                    break;
                default: goto out;
            }
            if(!use_nv){
                unsigned int ux;
                ux = uv << tn_shift;
                if(ux >> tn_shift != ux){
                    use_nv = 1;
                    nv = (double)uv;
                }
                else{
                    uv = ux | tc_digit;
                }
            }
            if(use_nv){
                nv *= pf_shift[tn_shift];
                nv += (double)tc_digit;
            }
        }
        out:
        if(use_nv){
            sv->type = SVt_float;
            sv->value.f = nv;
        }
        else{
            sv->type = SVt_int;
            sv->value.n = uv;
        }
    }
    else{
        ts_start = s;
        while(1){
            if(isdigit(*s)){
                tc_digit = *s & 0xf;
                if(use_nv){
                    nv = nv * 10.0 + tc_digit;
                }
                else{
                    uv = uv * 10 + tc_digit;
                }
            }
            else if(*s != '_'){
                break;
            }
            s++;
        }
        if(*s == '.' && s[1] != '.'){
            if(!use_nv){
                nv = (double)uv;
            }
            s++;
            tf_place = 10;
            while(isdigit(*s)){
                tc_digit = *s & 0xf;
                nv += tc_digit / tf_place;
                tf_place *= 10;
                s++;
            }
            if(*s == '.'){
                return f_get_v_string(ts_start, sv);
            }
        }
        if((*s=='e' || *s=='E')){
            if(!use_nv){
                nv = (double)uv;
            }
            s++;
            tb_sign = 1;
            if(*s == '-'){
                tb_sign = -1;
            }
            tn_exp = 0;
            while(isdigit(*s)){
                tn_exp = tn_exp * 10 + (*s & 0xf);
                s++;
            }
            if(tb_sign){
                tn_exp = -tn_exp;
            }
            nv /= pow(10, tn_exp);
        }
        if(!use_nv){
            sv->type = SVt_int;
            sv->value.n = uv;
        }
        else{
            sv->type = SVt_float;
            sv->value.f = nv;
        }
    }
    return s;
}

char* f_get_str_q(char* s, struct OP ** p_op){
    unsigned char c_begin;
    unsigned char c_end;
    char* s2;
    int n;
    char* t_s;
    int n_skip;
    struct SV* sv;
    struct OP* op;

    c_begin = *s;
    if(c_begin == '('){
        c_end = ')';
    }
    else if(c_begin == '['){
        c_end = ']';
    }
    else if(c_begin == '{'){
        c_end = '}';
    }
    else if(c_begin == '<'){
        c_end = '>';
    }
    else{
        c_end = c_begin;
    }
    s = f_scan_delim(s, &s2, &n);
    if(s && p_op){
        s2[n] = '\0';
        t_s = s2;
        n_skip = 0;
        while(*t_s){
            if(*t_s == '\\' && (t_s[1] == c_end || t_s[1] == '\\')){
                n_skip++;
                t_s++;
            }
            if(n_skip > 0){
                t_s[-n_skip] = *t_s;
            }
            t_s++;
        }
        n -= n_skip;
        sv = sv_from_s(s2, n);
        op = get_op();
        op->type = OP_CONST;
        op->right.op = NULL;
        op->right.sv = sv;
        *p_op = op;
    }
    return s;
}

char* f_get_str_qq(char* s, struct OP ** p_op){
    char* s2;
    int n;

    s = f_scan_delim(s, &s2, &n);
    if(s && p_op){
        s2[n] = '\0';
        *p_op = f_parse_str_qq(s2, 0);
    }
    return s;
}

void dump_parse_stack(struct TOK* stack, int i_top, struct TOK cur, char* s){
    int i;

    printf("  stack: ");
    for(i=0; i<i_top; i++){
        if(stack[i].type == T_BOC){
            printf("T_BOC%c, ", stack[i].value.n);
        }
        else if(stack[i].type == T_EOC){
            printf("T_EOC%c, ", stack[i].value.n);
        }
        else if(stack[i].type == T_ATOM){
            printf("[%s], ", get_OP_name(stack[i].value.op->type));
        }
        else{
            printf("%s, ", get_T_name(stack[i].type));
        }
    }
    printf("cur: %s\n", get_T_name(cur.type));
    if(s){
        printf("  src: [");
        puts(s);
    }
}

char* f_scan_word(char* s){
    while(isword(*s)){
        s++;
    }
    return s;
}

char* f_scan_id(char* s){
    while(1){
        if(isword(*s)){
            s++;
        }
        else if(s[0] == ':' && s[1] == ':'){
            s++;
        }
        else{
            return s;
        }
    }
}

int my_word(char* s, int n){
    switch(s[0]){
      case 'F':
        if(n==7 && strncmp(s, "FN_GOTO", 7)==0) return WORD_FN_GOTO;
        else if(n==4 && strncmp(s, "FN_1", 4)==0) return WORD_FN_1;
        break;
      case 'a':
        if(n==3 && strncmp(s, "and", 3)==0) return WORD_and;
        break;
      case 'c':
        if(n==3 && strncmp(s, "cmp", 3)==0) return WORD_cmp;
        else if(n==5 && strncmp(s, "close", 5)==0) return WORD_close;
        break;
      case 'd':
        if(n==3 && strncmp(s, "die", 3)==0) return WORD_die;
        break;
      case 'e':
        if(n==2 && strncmp(s, "eq", 2)==0) return WORD_eq;
        else if(n==5 && strncmp(s, "elsif", 5)==0) return WORD_elsif;
        else if(n==4 && strncmp(s, "else", 4)==0) return WORD_else;
        break;
      case 'f':
        if(n==5 && strncmp(s, "fread", 5)==0) return WORD_fread;
        else if(n==3 && strncmp(s, "for", 3)==0) return WORD_for;
        break;
      case 'g':
        if(n==2 && strncmp(s, "ge", 2)==0) return WORD_ge;
        else if(n==2 && strncmp(s, "gt", 2)==0) return WORD_gt;
        else if(n==4 && strncmp(s, "goto", 4)==0) return WORD_goto;
        break;
      case 'i':
        if(n==2 && strncmp(s, "if", 2)==0) return WORD_if;
        break;
      case 'j':
        if(n==4 && strncmp(s, "join", 4)==0) return WORD_join;
        break;
      case 'l':
        if(n==2 && strncmp(s, "le", 2)==0) return WORD_le;
        else if(n==2 && strncmp(s, "lt", 2)==0) return WORD_lt;
        else if(n==4 && strncmp(s, "last", 4)==0) return WORD_last;
        else if(n==2 && strncmp(s, "lc", 2)==0) return WORD_lc;
        else if(n==7 && strncmp(s, "lcfirst", 7)==0) return WORD_lcfirst;
        else if(n==5 && strncmp(s, "local", 5)==0) return WORD_local;
        break;
      case 'm':
        if(n==2 && strncmp(s, "my", 2)==0) return WORD_my;
        break;
      case 'n':
        if(n==2 && strncmp(s, "ne", 2)==0) return WORD_ne;
        else if(n==3 && strncmp(s, "not", 3)==0) return WORD_not;
        else if(n==4 && strncmp(s, "next", 4)==0) return WORD_next;
        else if(n==2 && strncmp(s, "no", 2)==0) return WORD_no;
        break;
      case 'o':
        if(n==2 && strncmp(s, "or", 2)==0) return WORD_or;
        else if(n==4 && strncmp(s, "open", 4)==0) return WORD_open;
        else if(n==3 && strncmp(s, "our", 3)==0) return WORD_our;
        break;
      case 'p':
        if(n==5 && strncmp(s, "print", 5)==0) return WORD_print;
        else if(n==6 && strncmp(s, "printf", 6)==0) return WORD_printf;
        else if(n==7 && strncmp(s, "package", 7)==0) return WORD_package;
        break;
      case 'q':
        if(n==9 && strncmp(s, "quotemeta", 9)==0) return WORD_quotemeta;
        break;
      case 'r':
        if(n==4 && strncmp(s, "redo", 4)==0) return WORD_redo;
        else if(n==6 && strncmp(s, "return", 6)==0) return WORD_return;
        else if(n==7 && strncmp(s, "require", 7)==0) return WORD_require;
        break;
      case 's':
        if(n==3 && strncmp(s, "sub", 3)==0) return WORD_sub;
        break;
      case 'u':
        if(n==2 && strncmp(s, "uc", 2)==0) return WORD_uc;
        else if(n==7 && strncmp(s, "ucfirst", 7)==0) return WORD_ucfirst;
        else if(n==3 && strncmp(s, "use", 3)==0) return WORD_use;
        break;
      case 'w':
        if(n==4 && strncmp(s, "warn", 4)==0) return WORD_warn;
        else if(n==5 && strncmp(s, "while", 5)==0) return WORD_while;
        break;
      case 'x':
        if(n==1 && strncmp(s, "x", 1)==0) return WORD_x;
        break;
    }
    return 0;
}

char* f_skip_simple_spaces(char* s){
    while(1){
        if(!s || s >= s_src_end){
            s = f_load_src(NULL);
            if(s == NULL){
                return s;
            }
        }
        if(isspace(*s)){
            s++;
        }
        else{
            return s;
        }
    }
}

int keyword_op(char* s){
    if(strncmp(s, "eq", 2) == 0){
        return T_eq;
    }
    else if(strncmp(s, "ne", 2) == 0){
        return T_ne;
    }
    else if(strncmp(s, "le", 2) == 0){
        return T_le;
    }
    else if(strncmp(s, "ge", 2) == 0){
        return T_ge;
    }
    else if(strncmp(s, "lt", 2) == 0){
        return T_lt;
    }
    else if(strncmp(s, "gt", 2) == 0){
        return T_gt;
    }
    else if(strncmp(s, "cmp", 3) == 0){
        return T_cmp;
    }
    else if(strncmp(s, "or", 2) == 0){
        return T_or;
    }
    else if(strncmp(s, "and", 3) == 0){
        return T_and;
    }
    else if(strncmp(s, "not", 3) == 0){
        return T_not;
    }
    else if(strncmp(s, "x", 1) == 0){
        return T_x;
    }
    return 0;
}

char* f_scan_delim(char* s, char** p_str, int* pn_len){
    char* ts_quick;
    unsigned char c_begin;
    unsigned char c_end;
    bool b_esc;
    int tn_level;
    struct buf_chain * head;
    struct buf_chain * tail;
    struct buf_chain * p;
    char* d;
    int n;
    char* s_tmp;

    ts_quick = f_scan_delim_quick(s);
    if(ts_quick){
        *p_str = s + 1;
        *pn_len = ts_quick - s - 1;
        return ts_quick + 1;
    }
    c_begin = *s;
    if(c_begin == '('){
        c_end = ')';
    }
    else if(c_begin == '['){
        c_end = ']';
    }
    else if(c_begin == '{'){
        c_end = '}';
    }
    else if(c_begin == '<'){
        c_end = '>';
    }
    else{
        c_end = c_begin;
    }
    s++;
    b_esc = 0;
    tn_level = 1;
    p=(struct buf_chain*)calloc(1, sizeof(struct buf_chain));
    head = p;
    tail = p;
    d = p->s;
    n = 0;
    while(1){
        if(s >= s_src_end){
            p->n = d - p->s;
            p=(struct buf_chain*)calloc(1, sizeof(struct buf_chain));
            tail->next = p;
            d = p->s;
            n = 0;
            s = f_load_src(NULL);
            if(s == NULL){
                return s;
            }
        }
        if(b_esc){
            b_esc = 0;
        }
        else{
            if(*s == '\\'){
                b_esc = 1;
            }
            else if(*s == c_end){
                tn_level--;
                if(tn_level == 0){
                    s++;
                    break;
                }
            }
            else if(*s == c_begin){
                tn_level--;
            }
        }
        *d++ = *s++;
    }
    n = 0;
    p = head;
    while(p){
        n += p->n;
        p = p->next;
    }
    s_tmp=(char*)malloc(n*sizeof(char));
    *p_str = s_tmp;
    *pn_len = n;
    p = head;
    while(p){
        memcpy(s_tmp, p->s, p->n);
        s_tmp += p->n;
        p = p->next;
        free(head);
        head = p;
    }
    return s;
}

void CV_begin(){
    if(cv_cur){
        cv_cur->n_vars = g_local_len - cv_cur->i_start;
        cv_cur->n_seq = i_seq;
    }
    if(lex_stack_len + 1 > lex_stack_size){
        lex_stack = f_darray_expand(lex_stack, sizeof(struct CV*), &lex_stack_size);
    }
    lex_stack[lex_stack_len] = cv_cur;
    lex_stack_len++;
    stash_local = stash_new();
    cv_cur = CV_new();
    cv_cur->stash = stash_local;
    cv_cur->i_file = cur_file_scope;
    cv_cur->i_start = g_local_len;
    cv_cur->debug = n_debug;
    if(n_debug){
        puts(">>>> cv begin");
    }
    i_seq = 0;
}

void SV_append_s(struct SV* sv, char* s, int n){
    if(!(sv->type == SVt_string)){
        puts("assert error: ! (sv->type==SVt_string)");
        exit(0);
    }
    SV_resize(sv, sv->value.S.n + n);
    memcpy(sv->value.S.s + sv->value.S.n, s, n);
    sv->value.S.n += n;
}

int find_global(char* s_name){
    char char_sigil;
    char* s;
    char* s_package_begin;
    char* s_package_end;
    struct stash* stash;
    int i;
    int tn_var;

    char_sigil = *s_name++;
    s = s_name;
    s_package_begin = s_name;
    s_package_end = NULL;
    while(*s){
        if(s[0] == ':' && s[1] == ':'){
            s += 2;
            s_package_end = s;
            s_name = s;
        }
        else{
            s++;
        }
    }
    if(s_package_end){
        stash = g_stashes[0];
        i = f_stash_get(stash, s_package_begin, s_package_end-s_package_begin);
        if(i > 0){
            stash = g_stashes[i];
        }
        else{
            return 0;
        }
        s_name -= 1;
        *s_name = char_sigil;
    }
    else{
        stash = stash_global;
        s_name -= 1;
    }
    tn_var = f_stash_get(stash, s_name, s-s_name);
    if(!tn_var && !s_package_end){
        stash = g_stashes[0];
        tn_var = f_stash_get(stash, s_name, s-s_name);
    }
    return tn_var;
}

int find_local(char* s_name){
    struct stash* stash;
    int i;
    int tn_var;

    stash = stash_local;
    i = lex_stack_len;
    while(1){
        tn_var = f_stash_get(stash, s_name, strlen(s_name));
        if(tn_var){
            return tn_var;
        }
        i--;
        if(i > 0){
            stash = lex_stack[i]->stash;
        }
        else{
            break;
        }
    }
    return 0;
}

struct OP* f_parse_var_special(char char_sigil, char* s){
    struct OP* op;

    op = NULL;
    if(char_sigil == '$'){
        if(s[1] == '['){
            char_sigil = '@';
        }
        else if(s[1] == '%'){
            char_sigil = '%';
        }
    }
    if(char_sigil == '$'){
        if(s[0] == '&'){
            op = get_op();
            op->type = OP_VarMatch;
            op->right.op = NULL;
            op->right.n = 0;
        }
        else if(s[0] >= '1' && s[0] <= '9'){
            op = get_op();
            op->type = OP_VarMatch;
            op->right.op = NULL;
            op->right.n = s[0] & 0xf;
        }
        else if(s[0] == '`'){
            op = get_op();
            op->type = OP_VarMatch;
            op->right.op = NULL;
            op->right.n = -1;
        }
        else if(s[0] == '\''){
            op = get_op();
            op->type = OP_VarMatch;
            op->right.op = NULL;
            op->right.n = -2;
        }
    }
    else if(char_sigil == '@'){
        if(s[0] == '_' && !isword(s[1])){
            s++;
            op = get_op();
            op->type = OP_GLOBAL;
            op->left.n = '@';
            op->right.n = I_at_ARG;
        }
    }
    else if(char_sigil == '%'){
    }
    return op;
}

char* f_scan_operator(char* s, int* p_id){
    switch(s[0]){
      case ',': *p_id = T_Comma; return s+1;
      case '!':
        if(s[1]=='='){*p_id = T_EmarkEq;return s+2;}
        else{*p_id = T_Emark;return s+1;}
        break;
      case '&':
        if(s[1]=='='){*p_id = T_AndEq;return s+2;}
        else{*p_id = T_And;return s+1;}
        break;
      case '*':
        if(s[1]=='*'){*p_id = T_MultMult;return s+2;}
        else if(s[1]=='='){*p_id = T_MultEq;return s+2;}
        else{*p_id = T_Mult;return s+1;}
        break;
      case '+':
        if(s[1]=='+'){*p_id = T_PlusPlus;return s+2;}
        else if(s[1]=='='){*p_id = T_PlusEq;return s+2;}
        else{*p_id = T_Plus;return s+1;}
        break;
      case '-':
        if(s[1]=='-'){*p_id = T_MinusMinus;return s+2;}
        else if(s[1]=='='){*p_id = T_MinusEq;return s+2;}
        else{*p_id = T_Minus;return s+1;}
        break;
      case '.':
        if(s[1]=='.'){*p_id = T_DotDot;return s+2;}
        else if(s[1]=='='){*p_id = T_DotEq;return s+2;}
        else{*p_id = T_Dot;return s+1;}
        break;
      case '/':
        if(s[1]=='='){*p_id = T_DivEq;return s+2;}
        else{*p_id = T_Div;return s+1;}
        break;
      case ':': *p_id = T_Colon;return s+1;
      case ';': *p_id = T_Semi;return s+1;
      case '<':
        if(s[1]=='<' && s[2]=='='){*p_id = T_LtLtEq;return s+3;}
        else if(s[1]=='='){*p_id = T_LtEq;return s+2;}
        else if(s[1]=='<'){*p_id = T_LtLt;return s+2;}
        else{*p_id = T_Lt;return s+1;}
        break;
      case '=':
        if(s[1]=='>'){*p_id = T_EqGt;return s+2;}
        else if(s[1]=='~'){*p_id = T_EqTlide;return s+2;}
        else if(s[1]=='='){*p_id = T_EqEq;return s+2;}
        else{*p_id = T_Eq;return s+1;}
        break;
      case '>':
        if(s[1]=='>' && s[2]=='='){*p_id = T_GtGtEq;return s+3;}
        else if(s[1]=='='){*p_id = T_GtEq;return s+2;}
        else if(s[1]=='>'){*p_id = T_GtGt;return s+2;}
        else{*p_id = T_Gt;return s+1;}
        break;
      case '?': *p_id = T_Qmark;return s+1;
      case '|':
        if(s[1]=='='){*p_id = T_OrEq;return s+2;}
        else{*p_id = T_Or;return s+1;}
        break;
      case '~': *p_id = T_Tlide;return s+1;
    }
    *p_id = 0;
    return s;
}

char* get_OP_name(int n_OP){
    return OP_names[(n_OP>>8)-1];
}

struct OP* f_new_op(int tn_type, struct OP* op_a, struct OP* op_b){
    struct OP* op;

    op = get_op();
    op->type = tn_type;
    op->left.op = op_a;
    op->right.op = op_b;
    return op;
}

struct CV* CV_close(struct OP* op_block){
    struct CV* cv;

    if(op_block->type == OP_SEQ){
        f_flatten_op_list(op_block, OP_SEQ);
        op_block->type = OP_block;
    }
    cv_cur->op_block = op_block;
    cv_cur->n_vars = g_local_len - cv_cur->i_start;
    cv_cur->n_seq = i_seq;
    cv = cv_cur;
    lex_stack_len--;
    cv_cur = lex_stack[lex_stack_len];
    if(cv_cur){
        g_local_len = cv_cur->i_start + cv_cur->n_vars;
        i_seq = cv_cur->n_seq;
        stash_local = cv_cur->stash;
    }
    if(n_debug){
        printf("<<<< cv close ---");
        fprintf(stdout, "    :lex_stack_len=%d, cv->n_vars=%d\n", lex_stack_len, cv->n_vars);
    }
    if(cv_cur){
        n_debug = cv_cur->debug;
    }
    return cv;
}

void f_flatten_op_list(struct OP* op, int tn_type){
    int n;
    struct OP* op_list;

    n = f_op_iter_count(op, tn_type);
    op_list = get_op_list(n);
    f_op_iter_get(op, tn_type, op_list);
    op->left.n = n;
    op->right.op = op_list;
}

struct OP* get_op_list(int n){
    if(i_op_free + n > n_op_free){
        if(n > 100){
            op_freelist=(struct OP*)calloc(n, sizeof(struct OP));
            if(heap_len + 1 > heap_size){
                heap = f_darray_expand(heap, sizeof(struct T), &heap_size);
            }
            heap[heap_len].a1 = HEAP_op;
            heap[heap_len].a2 = n;
            heap[heap_len].a3 = op_freelist;
            heap_len++;
            i_op_free = 0;
            n_op_free = n;
        }
        else{
            op_freelist=(struct OP*)calloc(100, sizeof(struct OP));
            if(heap_len + 1 > heap_size){
                heap = f_darray_expand(heap, sizeof(struct T), &heap_size);
            }
            heap[heap_len].a1 = HEAP_op;
            heap[heap_len].a2 = 100;
            heap[heap_len].a3 = op_freelist;
            heap_len++;
            i_op_free = 0;
            n_op_free = 100;
        }
        i_op_free = n;
        return op_freelist;
    }
    else{
        i_op_free += n;
        return op_freelist + i_op_free - n;
    }
}

struct SV* run_cv(struct CV* cv, int tn_context, int tn_level){
    int i_0;
    int i_n;
    int n_debug_save;
    struct OP* op_block;
    int n;
    struct OP* op_list;
    int i;
    struct SV* sv_ret;

    if(tn_level > 0){
        i_0 = cv->i_start;
        i_n = g_local_len;
        if(cv->n_vars > 0){
            memset(g_local + i_0, 0, cv->n_vars * sizeof(struct SV));
            g_local_len += cv->n_vars;
        }
        else{
            g_local_len = i_0;
        }
    }
    else{
        memset(g_local, 0, g_local_len * sizeof(struct SV));
    }
    if(cv->debug){
        n_debug_save = n_debug;
        n_debug = cv->debug;
        printf("---- enter_scope: 0 global vars, %d local vars \n", cv->n_vars);
    }
    op_block = cv->op_block;
    if(op_block->type == OP_block){
        n = op_block->left.n;
        op_list = op_block->right.op;
        i = 0;
        while(1){
            if(cv->debug){
                printf("cv_run %s [%d/%d]\n", cv->flag == CVf_loop ? "loop": "block", i, n);
                if(n_svreg != 0){
                    printf("    reg: %d\n", n_svreg);
                }
            }
            sv_ret = eval_op(&op_list[i], 0, 0);
            if(sv_ret && sv_ret->type == SVt_goto){
                if(sv_ret->value.G.i > 0){
                    if(!sv_ret->value.G.cv || sv_ret->value.G.cv == cv){
                        i = sv_ret->value.G.i;
                        if(i < n){
                            if(sv_ret && (sv_ret->flag & 3) == SVf_register){
                                SV_refdec(sv_ret);
                                sv_ret->flag = 0;
                                n_svreg--;
                            }
                            continue;
                        }
                    }
                    if(sv_ret && (sv_ret->flag & 3) == SVf_register){
                        SV_refdec(sv_ret);
                        sv_ret->flag = 0;
                        n_svreg--;
                    }
                    sv_ret = NULL;
                    break;
                }
                else{
                    if(sv_ret->value.G.cv != cv){
                        break;
                    }
                    else if(sv_ret->value.G.i == GOTO_return){
                        if(sv_ret && (sv_ret->flag & 3) == SVf_register){
                            SV_refdec(sv_ret);
                            sv_ret->flag = 0;
                            n_svreg--;
                        }
                        sv_ret = NULL;
                        break;
                    }
                    else if(cv->flag == CVf_loop){
                        if(sv_ret->value.G.i == GOTO_last){
                            if(sv_ret && (sv_ret->flag & 3) == SVf_register){
                                SV_refdec(sv_ret);
                                sv_ret->flag = 0;
                                n_svreg--;
                            }
                            sv_ret = NULL;
                            break;
                        }
                        else if(sv_ret->value.G.i == GOTO_next){
                            if(sv_ret && (sv_ret->flag & 3) == SVf_register){
                                SV_refdec(sv_ret);
                                sv_ret->flag = 0;
                                n_svreg--;
                            }
                            sv_ret = NULL;
                            i += 1;
                            continue;
                        }
                        else if(sv_ret->value.G.i == GOTO_redo){
                            i -= 1;
                            continue;
                        }
                    }
                    else{
                        if(sv_ret->value.G.i == GOTO_last || sv_ret->value.G.i == GOTO_next){
                            if(sv_ret && (sv_ret->flag & 3) == SVf_register){
                                SV_refdec(sv_ret);
                                sv_ret->flag = 0;
                                n_svreg--;
                            }
                            sv_ret = NULL;
                            break;
                        }
                        else if(sv_ret->value.G.i == GOTO_redo){
                            continue;
                        }
                    }
                }
            }
            i++;
            if(i < n){
                if(sv_ret && (sv_ret->flag & 3) == SVf_register){
                    SV_refdec(sv_ret);
                    sv_ret->flag = 0;
                    n_svreg--;
                }
            }
            else{
                break;
            }
        }
    }
    else{
        sv_ret = eval_op(cv->op_block, 0, tn_level + 1);
    }
    if(cv->debug){
        n_debug = n_debug_save;
        puts("---- leave_scope");
    }
    if(tn_level > 0){
        int i;
        for(i=i_0; i<g_local_len; i++){
            SV_refdec(&g_local[i]);
        }
        g_local_len = i_n;
    }
    return sv_ret;
}

struct SV* SV_copy(struct SV* sv_ret, struct SV* sv){
    if(!sv_ret){
        sv_ret = get_svreg(sv->type);
    }
    else{
        sv_ret->type = sv->type;
    }
    if(sv->type > SVt_BASIC && sv->value.p){
        if(!sv->copy){
            sv_ret->copy = sv->copy = get_copy();
        }
        else{
            svcopy[sv->copy]++;
            sv_ret->copy = sv->copy;
        }
    }
    memcpy(&sv_ret->value, &sv->value, sizeof(sv->value));
    return sv_ret;
}

struct SV* eval_list(struct OP* op_a, struct OP* op_b, int tn_context, int tn_level){
    struct SV* sv_b;
    struct SV* sv;
    struct AV* av;
    struct SV* sv_a;
    struct AV* av_item;

    sv_b = eval_op(op_b, 2, tn_level + 1);
    if(!op_a){
        if(sv_b->type == SVt_av){
            return sv_b;
        }
        else{
            sv = get_svreg(SVt_av);
            av = AV_new();
            sv->value.p = (void*)av;
        }
    }
    else{
        sv_a = eval_op(op_a, 2, tn_level + 1);
        if((sv_a->flag & 3) == SVf_register && sv_a->type == SVt_av){
            sv = sv_a;
            av = (struct AV*)sv->value.p;
        }
        else{
            sv = get_svreg(SVt_av);
            av = AV_new();
            sv->value.p = (void*)av;
            if(sv_a && sv_a->type == SVt_av){
                int i;
                av_item = (struct AV*)sv_a->value.p;
                if(!(av_item != av)){
                    puts("assert error: ! (av_item!=av)");
                    exit(0);
                }
                for(i=av_item->i_0; i<av_item->i_n; i++){
                    AV_push(av, av_item->p_array[i]);
                }
            }
            else{
                AV_push(av, sv_a);
            }
            if(sv_a && (sv_a->flag & 3) == SVf_register){
                SV_refdec(sv_a);
                sv_a->flag = 0;
                n_svreg--;
            }
        }
    }
    if(sv_b && sv_b->type == SVt_av){
        int i;
        av_item = (struct AV*)sv_b->value.p;
        if(!(av_item != av)){
            puts("assert error: ! (av_item!=av)");
            exit(0);
        }
        for(i=av_item->i_0; i<av_item->i_n; i++){
            AV_push(av, av_item->p_array[i]);
        }
    }
    else{
        AV_push(av, sv_b);
    }
    if(sv_b && (sv_b->flag & 3) == SVf_register){
        SV_refdec(sv_b);
        sv_b->flag = 0;
        n_svreg--;
    }
    return sv;
}

struct SV* get_svreg(int tn_type){
    struct SV* sv;

    if(n_svreg >= 100){
        fprintf(stderr, "Out of SV registers!\n");
        exit(-1);
    }
    while(svregs[i_svreg].flag){
        i_svreg = (i_svreg + 1) % 100;
    }
    sv = &svregs[i_svreg];
    sv->flag = SVf_register;
    sv->type = tn_type;
    sv->refcnt = 1;
    memset(&sv->value, 0, sizeof(sv->value));
    n_svreg++;
    return sv;
}

int do_bool(struct SV* sv){
    struct AV* av;

    if(!sv){
        return 0;
    }
    else if(sv->type == SVt_int){
        return sv->value.n != 0;
    }
    else if(sv->type == SVt_float){
        return sv->value.f != 0.0;
    }
    else if(sv->type == SVt_string){
        if(sv->value.S.n == 0){
            return 0;
        }
        else if(sv->value.S.n == 1 && sv->value.S.s[0] == '0'){
            return 0;
        }
        else{
            return 1;
        }
    }
    else if(sv->type == SVt_av){
        av = (struct AV*)sv->value.p;
        return (av->i_n - av->i_0) > 0;
    }
    else{
        return sv->value.p != NULL;
    }
}

void SV_to_int(struct SV* sv){
    double f;
    struct SV* sv_tmp;
    int n;

    if(sv->type == SVt_int){
        return;
    }
    else if(sv->type == SVt_float){
        f = sv->value.f;
        sv->type = SVt_int;
        sv->value.n = (int)f;
    }
    else if(sv->type == SVt_string){
        sv_tmp = get_svreg(SVt_undef);
        sv_tmp->type = SVt_string;
        sv_tmp->refcnt = 1;
        memset(&sv_tmp->value, 0, sizeof(sv_tmp->value));
        sv_tmp->value.S.s = sv->value.S.s;
        sv_tmp->value.S.n = sv->value.S.n;
        sv_tmp->value.S.size = sv->value.S.size;
        n = sv_string_int(sv);
        sv->type = SVt_int;
        sv->value.n = n;
        if(sv_tmp && (sv_tmp->flag & 3) == SVf_register){
            SV_refdec(sv_tmp);
            sv_tmp->flag = 0;
            n_svreg--;
        }
    }
}

struct SV* AV_get(struct AV* av, int i){
    int j;

    j = av->i_0 + i;
    if(j < av->i_n){
        return av->p_array[j];
    }
    else{
        return NULL;
    }
}

struct SV * AV_shift(struct AV* av){
    if(av->i_n > av->i_0){
        av->i_0++;
        return av->p_array[av->i_0-1];
    }
    return NULL;
}

void do_print(struct SV* sv_io, struct AV* av){
    FILE* file_out;
    int i;
    struct SV* sv;
    char* s;
    int n;

    file_out = (FILE*)sv_io->value.p;
    for(i=av->i_0; i<av->i_n; i++){
        sv = av->p_array[i];
        if(sv->type == SVt_string){
            s = sv->value.S.s;
            n = sv->value.S.n;
            s[n] = '\0';
            fputs(s, file_out);
        }
        else if(sv->type == SVt_int){
            fprintf(file_out, "%d", sv->value.n);
        }
        else if(sv->type == SVt_float){
            fprintf(file_out, "%f", sv->value.f);
        }
        else{
            puts("print unsupported sv");
            exit(0);
        }
    }
}

void do_printf(struct SV* sv_io, struct AV* av){
    FILE* file_out;
    struct SV* sv_fmt;
    char* s_fmt;
    char* s_end;
    char* s;
    int i_arg;
    char char_save;
    struct SV* sv;
    struct SV* sv_str;

    file_out = stdout;
    sv_fmt = AV_get(av, 0);
    if(sv_fmt && sv_fmt->type == SVt_string){
        s_fmt = sv_fmt->value.S.s;
        s_end = s_fmt + sv_fmt->value.S.n;
        s = s_fmt;
        i_arg = 1;
        while(1){
            if(s == s_end){
                if(s > s_fmt){
                    char_save = s[0];
                    s[0] = '\0';
                    fputs(s_fmt, file_out);
                    s[0] = char_save;
                }
                break;
            }
            else if(*s == '%'){
                if(s[1] == '%'){
                    if(s > s_fmt){
                        char_save = s[1];
                        s[1] = '\0';
                        fputs(s_fmt, file_out);
                        s[1] = char_save;
                    }
                    s_fmt = s + 2;
                    continue;
                }
                else{
                    if(s > s_fmt){
                        char_save = s[0];
                        s[0] = '\0';
                        fputs(s_fmt, file_out);
                        s[0] = char_save;
                    }
                    s++;
                    while((*s=='-' || *s=='+' || *s==' ' || *s=='0' || *s=='#')){
                        s++;
                    }
                    while(isdigit(*s)){
                        s++;
                    }
                    if(*s == '.'){
                        s++;
                        while(isdigit(*s)){
                            s++;
                        }
                    }
                    if((*s=='h' || *s=='l')){
                        if((s[1]=='h' || s[1]=='l')){
                            s += 2;
                        }
                        else{
                            s += 1;
                        }
                    }
                    else if((*s=='j' || *s=='q' || *s=='L' || *s=='t' || *s=='z')){
                        s += 1;
                    }
                    if((*s=='c' || *s=='s' || *s=='d' || *s=='u' || *s=='o' || *s=='x' || *s=='e' || *s=='f' || *s=='g' || *s=='X' || *s=='E' || *s=='G' || *s=='b' || *s=='B' || *s=='p')){
                        sv = AV_get(av, i_arg++);
                        sv_str = SV_fmt(sv, *s, 0, 0, 0);
                        sv_str->value.S.s[sv_str->value.S.n] = '\0';
                        fputs(sv_str->value.S.s, file_out);
                        if(sv_str && (sv_str->flag & 3) == SVf_register){
                            SV_refdec(sv_str);
                            sv_str->flag = 0;
                            n_svreg--;
                        }
                        s++;
                        s_fmt = s;
                        continue;
                    }
                    else{
                        s++;
                        continue;
                    }
                }
            }
            s++;
        }
    }
}

char * get_WORD_name(int id){
    if(id < 1){
        return NULL;
    }
    else if(id <= sizeof(WORD_names) / sizeof(char*)){
        return WORD_names[id-1];
    }
    return NULL;
}

struct SV* HV_get(struct HV* hv, char* s_key, int len){
    int k;

    k = f_strhash_lookup(hv, (unsigned char*)s_key, len);
    if(hv->p_exist[k]){
        return hv->p_val[k];
    }
    else{
        return NULL;
    }
}

void HV_set(struct HV* hv, char* s_key, int len, struct SV* sv_value){
    int k;

    k = f_strhash_lookup_left(hv, (unsigned char*)s_key, len);
    hv->p_val[k] = sv_value;
}

int do_int(struct SV* sv){
    struct AV* av;

    if(!sv || sv->type == SVt_undef){
        return 0;
    }
    else if(sv->type == SVt_int){
        return sv->value.n;
    }
    else if(sv->type == SVt_float){
        return (int)sv->value.f;
    }
    else if(sv->type == SVt_av){
        av = (struct AV*)sv->value.p;
        return av->i_n - av->i_0;
    }
    else{
        fprintf(stderr, "do_int type not supported [%s]\n", get_SV_name(sv->type));
        exit(-1);
    }
}

void AV_set(struct AV* av, int i, struct SV* sv_value){
    int j;

    j = av->i_0 + i;
    if(j < av->i_0){
        AV_unshift(av, av->i_0 - j);
    }
    else if(j >= av->i_n){
        AV_grow(av, j - av->i_n + 1);
    }
    av->p_array[av->i_0+j] = sv_value;
}

void do_assign(struct SV* sv_var, struct SV* sv_val){
    struct AV* av;
    struct HV* hv;
    struct SV* sv_key;

    if(!sv_var){
        return;
    }
    SV_undef(sv_var);
    if(!sv_val){
        return ;
    }
    if(sv_var->type == SVt_hv){
        if(sv_val->type == SVt_av){
            int i;
            av = (struct AV*)sv_val->value.p;
            hv = (struct HV*)sv_var->value.p;
            if(!hv){
                hv = HV_new();
                sv_var->value.p = hv;
            }
            for(i=av->i_0; i<av->i_n; i+=2){
                sv_key = do_string(av->p_array[i]);
                if(sv_key && sv_key->type == SVt_string){
                    HV_set(hv, sv_key->value.S.s, sv_key->value.S.n, av->p_array[i+1]);
                }
                else{
                    fprintf(stderr, "error\n");
                    exit(-1);
                }
            }
            return ;
        }
        else{
            fprintf(stderr, "Error\n");
            exit(-1);
        }
    }
    if(sv_var->type == SVt_av){
        if(sv_val->type != SVt_av){
            fprintf(stderr, "Error\n");
            exit(-1);
        }
    }
    SV_copy(sv_var, sv_val);
}

void SV_undef(struct SV* sv){
    SV_refdec(sv);
    memset(&sv->value, 0, sizeof(sv->value));
    if(!(sv->type == SVt_av || sv->type == SVt_hv)){
        sv->type = SVt_undef;
    }
}

void AV_free(struct AV* av){
    if(n_debug){
        printf("AV_free %p\n", av);
    }
    if(av->p_array){
        int i;
        for(i=av->i_0; i<av->i_n; i++){
            if(av->p_array[i]){
                SV_refdec(av->p_array[i]);
            }
        }
        free(av->p_array);
    }
    free(av);
}

void SV_append_sv(struct SV* sv, struct SV* sv_b){
    struct SV* sv_s_b;

    sv_s_b = do_string(sv_b);
    if(sv_s_b){
        SV_append_s(sv, sv_s_b->value.S.s, sv_s_b->value.S.n);
        if(sv_s_b && (sv_s_b->flag & 3) == SVf_register){
            SV_refdec(sv_s_b);
            sv_s_b->flag = 0;
            n_svreg--;
        }
    }
}

float do_float(struct SV* sv){
    if(!sv || sv->type == SVt_undef){
        return 0.0;
    }
    else if(sv->type == SVt_int){
        return (double)sv->value.n;
    }
    else if(sv->type == SVt_float){
        return sv->value.f;
    }
    else{
        return (double)do_int(sv);
    }
}

void SV_string_on_write(struct SV* sv){
    char* s;
    int n;
    int16_t n2;

    if(!(sv->type == SVt_string)){
        puts("assert error: ! (sv->type == SVt_string)");
        exit(0);
    }
    if(sv->copy){
        int i;
        i = sv->copy;
        sv->copy = 0;
        if(!(svcopy[i] > 0)){
            puts("assert error: ! (svcopy[i]>0)");
            exit(0);
        }
        svcopy[i]--;
        if(svcopy[i] == 0){
            n_svcopy--;
        }
        else{
            s = sv->value.S.s;
            n = sv->value.S.n;
            n2 = n + 20;
            sv->value.S.s = malloc(n2);
            memcpy(sv->value.S.s, s, n);
            sv->value.S.n = n;
            sv->value.S.size = n2;
            sv->value.S.pos = 0;
        }
    }
}

void SV_to_string(struct SV* sv){
    int n;
    double f;

    if(sv->type == SVt_string){
        return;
    }
    else if(sv->type == SVt_int){
        n = sv->value.n;
        sv->type = SVt_string;
        sv->refcnt = 1;
        memset(&sv->value, 0, sizeof(sv->value));
        SV_append_i(sv, n);
        return ;
    }
    else if(sv->type == SVt_float){
        f = sv->value.f;
        sv->type = SVt_string;
        sv->refcnt = 1;
        memset(&sv->value, 0, sizeof(sv->value));
        SV_append_f(sv, f);
        return ;
    }
}

void SV_to_float(struct SV* sv){
    int n;
    struct SV* sv_tmp;
    double f;

    if(sv->type == SVt_float){
        return;
    }
    else if(sv->type == SVt_int){
        n = sv->value.n;
        sv->type = SVt_float;
        sv->value.f = n;
    }
    else if(sv->type == SVt_string){
        sv_tmp = get_svreg(SVt_undef);
        sv_tmp->type = SVt_string;
        sv_tmp->refcnt = 1;
        memset(&sv_tmp->value, 0, sizeof(sv_tmp->value));
        sv_tmp->value.S.s = sv->value.S.s;
        sv_tmp->value.S.n = sv->value.S.n;
        sv_tmp->value.S.size = sv->value.S.size;
        f = sv_string_float(sv);
        sv->type = SVt_float;
        sv->value.f = f;
        if(sv_tmp && (sv_tmp->flag & 3) == SVf_register){
            SV_refdec(sv_tmp);
            sv_tmp->flag = 0;
            n_svreg--;
        }
    }
}

void SV_append_i(struct SV* sv, int i){
    int n;

    if(!(sv->type == SVt_string)){
        puts("assert error: ! (sv->type==SVt_string)");
        exit(0);
    }
    SV_resize(sv, sv->value.S.n + 30);
    n = sprintf(sv->value.S.s + sv->value.S.n, "%d", i);
    sv->value.S.n += n;
}

void SV_append_f(struct SV* sv, double f){
    int n;

    if(!(sv->type == SVt_string)){
        puts("assert error: ! (sv->type==SVt_string)");
        exit(0);
    }
    SV_resize(sv, sv->value.S.n + 30);
    n = sprintf(sv->value.S.s + sv->value.S.n, "%.8g", f);
    sv->value.S.n += n;
}

char* get_SV_name(int n_type){
    return SV_names[n_type];
}

void HV_free(struct HV* hv){
    int i;

    for(i=0; i<hv->n_size; i++){
        if(hv->p_exist[i]){
        }
    }
    free(hv->p_key);
    free(hv->p_exist);
    free(hv->p_val);
    free(hv->pool.pn_str);
    free(hv->pool.pc_pool);
}

char* f_load_src(char* s){
    int n;
    int n_extra;
    char* ts_min;
    int tn_tmp;

    if(s && s < s_src_end){
        return s;
    }
    if(!file_src){
        return NULL;
    }
    if(n_src_extra){
        memmove(s_src_buffer, s_src_end, n_src_extra);
        n = n_src_extra + fread(s_src_buffer + n_src_extra, 1, 1024 - n_src_extra, file_src);
    }
    else{
        n = fread(s_src_buffer, 1, 1024, file_src);
    }
    n_extra = 0;
    if(n == 1024){
        s = &s_src_buffer[n-1];
        ts_min = &s_src_buffer[10];
        tn_tmp = 0;
        while(1){
            if(*s == '\n'){
                break;
            }
            else if(*s == ' '){
                tn_tmp = n_extra;
            }
            s--;
            n_extra++;
            if(s <= ts_min){
                if(tn_tmp > 0){
                    n_src_extra = tn_tmp;
                }
                else{
                    n_src_extra = 0;
                }
                break;
            }
        }
        n -= n_src_extra;
    }
    else if(n == 0){
        return NULL;
    }
    s_src_end = s_src_buffer + n;
    *s_src_end = '\0';
    return s_src_buffer;
}

char* f_skip_line(char* s){
    while(1){
        if(!s || s >= s_src_end){
            s = f_load_src(NULL);
            if(s == NULL){
                return s;
            }
        }
        if(*s != '\n'){
            if(*s == 'D'){
                if(strncmp(s, "DEBUG", 5) == 0){
                    n_debug = 1;
                }
            }
            s++;
        }
        else{
            s++;
            return s;
        }
    }
}

struct OP* f_parse_str_qq(char* s, bool is_regex){
    struct OP* op = NULL;
    char* d = s;
    char* s_begin;
    int tn_num;
    char* ts_save;
    int t_n;
    struct SV* sv;
    struct OP* op_right;
    struct OP* op_left;
    struct OP* op_tmp;
    int tn_word;
    char* ts_sigil;
    char char_sigil;
    struct OP* op_var;
    struct OP* op_sep;
    struct OP* op_list;

    s_begin = s;
    while(*s){
        if(*s == '\\'){
            switch(s[1]){
                case 'n':
                    *d++ = '\n';
                    s += 2;
                    continue;
                case 't':
                    *d++ = '\t';
                    s += 2;
                    continue;
                case 'r':
                    *d++ = '\r';
                    s += 2;
                    continue;
                case 'f':
                    *d++ = '\f';
                    s += 2;
                    continue;
                case 'a':
                    *d++ = '\a';
                    s += 2;
                    continue;
                case 'b':
                    *d++ = '\b';
                    s += 2;
                    continue;
                case 'e':
                    *d++ = '\x1b';
                    s += 2;
                    continue;
                case '0':
                    if(isoct(s[2]) && isoct(s[3])){
                        *d++ = (s[2] & 0xf) * 8 + (s[3] & 0xf);
                        s += 4;
                        continue;
                    }
                    else{
                        break;
                    }
                case 'x':
                    tn_num = hex(s + 2, 2);
                    if(s[2] == '{'){
                        ts_save = s;
                        s = f_scan_delim_quick(s + 2);
                        if(s){
                            tn_num = hex(s, s - ts_save);
                            if(tn_num >= 0){
                                t_n = utf(d, tn_num);
                                if(t_n > 0){
                                    d += t_n;
                                    continue;
                                }
                            }
                            s += 1;
                        }
                        fprintf(stderr, "string \\x{code}\n");
                        exit(-1);
                    }
                    else if(tn_num >= 0){
                        *d = tn_num;
                        s += 4;
                        continue;
                    }
                    else{
                        break;
                    }
                case 'c':
                    if(isalpha(s[2])){
                        *d++ = s[2] & 0xf;
                        s += 3;
                        continue;
                    }
                    else{
                        break;
                    }
                case 'u':
                case 'l':
                    if(s[2]){
                        if(d > s_begin){
                            sv = sv_from_s(s_begin, d - s_begin);
                            op_right = get_op();
                            op_right->type = OP_CONST;
                            op_right->right.op = NULL;
                            op_right->right.sv = sv;
                            if(!op){
                                op = op_right;
                            }
                            else{
                                op_left = op;
                                op = get_op();
                                op->type = OP_Dot;
                                op->left.op = op_left;
                                op->right.op = op_right;
                            }
                        }
                        op_tmp = f_parse_str_qq(s + 2, is_regex);
                        if(s[1] == 'u'){
                            tn_word = WORD_ucfirst;
                        }
                        else{
                            tn_word = WORD_lcfirst;
                        }
                        op_right = get_op();
                        op_right->type = OP_UNARY;
                        op_right->left.n = tn_word;
                        op_right->right.op = op_tmp;
                        if(!op){
                            op = op_right;
                        }
                        else{
                            op_left = op;
                            op = get_op();
                            op->type = OP_Dot;
                            op->left.op = op_left;
                            op->right.op = op_right;
                        }
                        return op;
                    }
                    else{
                        fprintf(stderr, "string \[ul] at end\n");
                        exit(-1);
                    }
                case 'U':
                case 'L':
                case 'Q':
                    ts_save = s;
                    s += 2;
                    while(*s){
                        if(s[0] == '\\' && s[1] == 'E'){
                            break;
                        }
                        s++;
                    }
                    if(s[0] == '\\'){
                        s[0] = '\0';
                        if(d > s_begin){
                            sv = sv_from_s(s_begin, d - s_begin);
                            op_right = get_op();
                            op_right->type = OP_CONST;
                            op_right->right.op = NULL;
                            op_right->right.sv = sv;
                            if(!op){
                                op = op_right;
                            }
                            else{
                                op_left = op;
                                op = get_op();
                                op->type = OP_Dot;
                                op->left.op = op_left;
                                op->right.op = op_right;
                            }
                        }
                        op_tmp = f_parse_str_qq(ts_save + 2, is_regex);
                        if(ts_save[1] == 'U'){
                            tn_word = WORD_uc;
                        }
                        else if(ts_save[1] == 'L'){
                            tn_word = WORD_lc;
                        }
                        else{
                            tn_word = WORD_quotemeta;
                        }
                        op_right = get_op();
                        op_right->type = OP_UNARY;
                        op_right->left.n = tn_word;
                        op_right->right.op = op_tmp;
                        if(!op){
                            op = op_right;
                        }
                        else{
                            op_left = op;
                            op = get_op();
                            op->type = OP_Dot;
                            op->left.op = op_left;
                            op->right.op = op_right;
                        }
                        s += 2;
                        s_begin = d = s;
                        continue;
                    }
                    else{
                        fprintf(stderr, "unterminated \[ULQ]\n");
                        exit(-1);
                    }
            }
            if(!is_regex){
                *d++ = s[1];
                s += 2;
                continue;
            }
        }
        else if((*s=='$' || *s=='@')){
            ts_sigil = s;
            char_sigil = *s;
            if((s[1]=='_' || (s[1]>='1'&&s[1]<='9'))){
                op_var = f_parse_var(s, 2);
                if(char_sigil == '@'){
                    op_sep = get_op();
                    op_sep->type = OP_GLOBAL;
                    op_sep->left.n = '$';
                    op_sep->right.n = I_LIST_SEPARATOR;
                    op_list = get_op();
                    op_list->type = OP_LIST;
                    op_list->left.op = op_sep;
                    op_list->right.op = op_var;
                    op_var = get_op();
                    op_var->type = OP_join;
                    op_var->right.op = NULL;
                    op_var->right.op = op_list;
                }
                if(d > s_begin){
                    sv = sv_from_s(s_begin, d - s_begin);
                    op_right = get_op();
                    op_right->type = OP_CONST;
                    op_right->right.op = NULL;
                    op_right->right.sv = sv;
                    if(!op){
                        op = op_right;
                    }
                    else{
                        op_left = op;
                        op = get_op();
                        op->type = OP_Dot;
                        op->left.op = op_left;
                        op->right.op = op_right;
                    }
                }
                if(!op){
                    op = op_var;
                }
                else{
                    op_left = op;
                    op = get_op();
                    op->type = OP_Dot;
                    op->left.op = op_left;
                    op->right.op = op_var;
                }
                s += 2;
                s_begin = d = s;
                continue;
            }
            else if(!isword1st(s[1]) && s[1] != '{'){
                *d++ = *s++;
                continue;
            }
            else if(s[1] == '{'){
                s = f_scan_delim_quick(s + 1);
                s++;
                op_var = f_parse_var(ts_sigil, s - ts_sigil);
                if(char_sigil == '@'){
                    op_sep = get_op();
                    op_sep->type = OP_GLOBAL;
                    op_sep->left.n = '$';
                    op_sep->right.n = I_LIST_SEPARATOR;
                    op_list = get_op();
                    op_list->type = OP_LIST;
                    op_list->left.op = op_sep;
                    op_list->right.op = op_var;
                    op_var = get_op();
                    op_var->type = OP_join;
                    op_var->right.op = NULL;
                    op_var->right.op = op_list;
                }
                if(d > s_begin){
                    sv = sv_from_s(s_begin, d - s_begin);
                    op_right = get_op();
                    op_right->type = OP_CONST;
                    op_right->right.op = NULL;
                    op_right->right.sv = sv;
                    if(!op){
                        op = op_right;
                    }
                    else{
                        op_left = op;
                        op = get_op();
                        op->type = OP_Dot;
                        op->left.op = op_left;
                        op->right.op = op_right;
                    }
                }
                if(!op){
                    op = op_var;
                }
                else{
                    op_left = op;
                    op = get_op();
                    op->type = OP_Dot;
                    op->left.op = op_left;
                    op->right.op = op_var;
                }
                s_begin = d = s;
                continue;
            }
            else{
                s++;
                while(*s == '$'){
                    s++;
                }
                s = f_scan_word(s + 1);
                if(*ts_sigil == '$'){
                    while(1){
                        if(*s == '[' || *s == '{'){
                            ts_save = s;
                            s = f_scan_delim_quick(s);
                            if(s){
                                s++;
                            }
                            else{
                                s = ts_save;
                                break;
                            }
                        }
                        else if(s[0] == '-' && s[1] == '>' && (s[2] == '[' || s[2] == '{')){
                            ts_save = s;
                            s = f_scan_delim_quick(s + 2);
                            if(s){
                                s++;
                            }
                            else{
                                s = ts_save;
                                break;
                            }
                        }
                        else{
                            break;
                        }
                    }
                }
                op_var = f_parse_var(ts_sigil, s - ts_sigil);
                if(char_sigil == '@'){
                    op_sep = get_op();
                    op_sep->type = OP_GLOBAL;
                    op_sep->left.n = '$';
                    op_sep->right.n = I_LIST_SEPARATOR;
                    op_list = get_op();
                    op_list->type = OP_LIST;
                    op_list->left.op = op_sep;
                    op_list->right.op = op_var;
                    op_var = get_op();
                    op_var->type = OP_join;
                    op_var->right.op = NULL;
                    op_var->right.op = op_list;
                }
                if(d > s_begin){
                    sv = sv_from_s(s_begin, d - s_begin);
                    op_right = get_op();
                    op_right->type = OP_CONST;
                    op_right->right.op = NULL;
                    op_right->right.sv = sv;
                    if(!op){
                        op = op_right;
                    }
                    else{
                        op_left = op;
                        op = get_op();
                        op->type = OP_Dot;
                        op->left.op = op_left;
                        op->right.op = op_right;
                    }
                }
                if(!op){
                    op = op_var;
                }
                else{
                    op_left = op;
                    op = get_op();
                    op->type = OP_Dot;
                    op->left.op = op_left;
                    op->right.op = op_var;
                }
                s_begin = d = s;
                continue;
            }
        }
        *d++ = *s;
        s++;
    }
    if(d > s_begin){
        sv = sv_from_s(s_begin, d - s_begin);
        op_right = get_op();
        op_right->type = OP_CONST;
        op_right->right.op = NULL;
        op_right->right.sv = sv;
        if(!op){
            op = op_right;
        }
        else{
            op_left = op;
            op = get_op();
            op->type = OP_Dot;
            op->left.op = op_left;
            op->right.op = op_right;
        }
    }
    return op;
}

char* f_get_v_string(char* s, struct SV* sv){
    unsigned int u = 0;
    unsigned char pc_buf[8];
    int n = 0;

    memset(sv, 0, sizeof(*sv));
    sv->type = SVt_string;
    while(1){
        if(isdigit(*s)){
            u = u * 10 + (*s & 0xf);
        }
        else if(*s == '_'){
        }
        else if(*s == '.'){
            if(u < 256){
                pc_buf[n++] = u;
            }
            else{
                puts("not supported vstring char");
                exit(0);
            }
            SV_append_s(sv, (char*)pc_buf, n);
        }
        else{
            break;
        }
        s++;
    }
    if(u < 256){
        pc_buf[n++] = u;
    }
    else{
        puts("not supported vstring char");
        exit(0);
    }
    SV_append_s(sv, (char*)pc_buf, n);
    return s;
}

char * get_T_name(int n_type){
    int tn_op;

    tn_op = n_type >> 8;
    if(tn_op){
        return T_op_names[tn_op-1];
    }
    else{
        return "T_ATOM";
    }
}

char* f_scan_delim_quick(char* s){
    unsigned char c_begin;
    unsigned char c_end;
    char* ts_orig;
    int tn_level;

    c_begin = *s;
    if(c_begin == '('){
        c_end = ')';
    }
    else if(c_begin == '['){
        c_end = ']';
    }
    else if(c_begin == '{'){
        c_end = '}';
    }
    else if(c_begin == '<'){
        c_end = '>';
    }
    else{
        c_end = c_begin;
    }
    s++;
    ts_orig = s;
    tn_level = 1;
    while(*s){
        if(*s == '\\'){
            s++;
        }
        else if(*s == c_end){
            tn_level--;
            if(tn_level == 0){
                break;
            }
        }
        else if(*s == c_begin){
            tn_level++;
        }
        s++;
    }
    if(*s){
        return s;
    }
    else{
        return NULL;
    }
}

struct CV* CV_new(){
    struct CV* cv;

    cv=(struct CV*)calloc(1, sizeof(struct CV));
    return cv;
}

int f_op_iter_count(struct OP* op, int tn_type){
    int8_t n1;
    int16_t n2;

    if(op->type != tn_type){
        return 1;
    }
    else{
        n1 = f_op_iter_count(op->left.op, tn_type);
        n2 = f_op_iter_count(op->right.op, tn_type);
        return n1 + n2;
    }
}

struct OP* f_op_iter_get(struct OP* op, int tn_type, struct OP* op_list){
    struct OP* op_next;

    if(op->type != tn_type){
        *op_list = *op;
        return op_list + 1;
    }
    else{
        op_next = f_op_iter_get(op->left.op, tn_type, op_list);
        return f_op_iter_get(op->right.op, tn_type, op_next);
    }
}

int get_copy(){
    if(n_svcopy >= 100){
        fprintf(stderr, "Out of COPY counters!\n");
        exit(-1);
    }
    while(svcopy[i_svcopy]){
        i_svcopy = (i_svcopy + 1) % 100;
    }
    svcopy[i_svcopy] = 2;
    n_svcopy++;
    return i_svcopy;
}

int sv_string_int(struct SV* sv){
    struct SV* sv_tmp;
    int n;

    sv_tmp = get_svreg(SVt_undef);
    sv->value.S.s[sv->value.S.n] = '\0';
    f_get_number(sv->value.S.s, sv_tmp);
    n = do_int(sv_tmp);
    if(sv_tmp && (sv_tmp->flag & 3) == SVf_register){
        SV_refdec(sv_tmp);
        sv_tmp->flag = 0;
        n_svreg--;
    }
    return n;
}

struct SV* SV_fmt(struct SV* sv, char char_fmt, int n_width, int n_prec, int n_flag){
    int n;
    struct SV* sv_ret;
    double f;

    if(!sv){
        if(char_fmt == 's'){
            return sv_EMPTY;
        }
        else{
            sv = sv_FALSE;
        }
    }
    if(char_fmt == 's'){
        if(sv->type == SVt_string){
            return sv;
        }
        else{
            return do_string(sv);
        }
    }
    if(char_fmt == 'd'){
        n = do_int(sv);
        sv_ret = get_svreg(SVt_string);
        sv_ret->value.S.s = NULL;
        sv_ret->value.S.n = 0;
        sv_ret->value.S.size = 0;
        SV_append_i(sv_ret, n);
        return sv_ret;
    }
    if(char_fmt == 'f'){
        f = do_float(sv);
        sv_ret = get_svreg(SVt_string);
        sv_ret->value.S.s = NULL;
        sv_ret->value.S.n = 0;
        sv_ret->value.S.size = 0;
        SV_append_f(sv_ret, f);
        return sv_ret;
    }
    return NULL;
}

void AV_unshift(struct AV* av, int n){
    int size;

    if(av->i_0 <= n){
        size = (av->i_n - av->i_0) + n + 10 * 2;
        AV_resize(av, -size);
    }
    av->i_0 -= n;
    memset(av->p_array + av->i_0, 0, sizeof(struct SV*) * n);
}

void AV_grow(struct AV* av, int n){
    int size;

    if(av->i_n + n >= av->size){
        size = (av->i_n - av->i_0) + n + 10 * 2;
        AV_resize(av, size);
    }
    memset(av->p_array + av->i_n, 0, sizeof(struct SV*) * n);
    av->i_n += n;
}

struct HV* HV_new(){
    struct HV* hv;

    hv=(struct HV*)calloc(1, sizeof(struct HV));
    hv->n_val_size = sizeof(struct SV*);
    return hv;
}

double sv_string_float(struct SV* sv){
    struct SV* sv_tmp;
    double f;

    sv_tmp = get_svreg(SVt_undef);
    sv->value.S.s[sv->value.S.n] = '\0';
    f_get_number(sv->value.S.s, sv_tmp);
    f = do_float(sv_tmp);
    if(sv_tmp && (sv_tmp->flag & 3) == SVf_register){
        SV_refdec(sv_tmp);
        sv_tmp->flag = 0;
        n_svreg--;
    }
    return f;
}

int hex(char* s, int n){
    int n_sum;
    int i;
    int t_n;

    n_sum = 0;
    for(i=0; i<n; i++){
        if(s[i] >= '0' && s[i] <= '9'){
            t_n = s[i] & 0xf;
        }
        else if(s[i] >= 'a' && s[i] <= 'f'){
            t_n = (s[i] & 0xf) + 9;
        }
        else if(s[i] >= 'A' && s[i] <= 'F'){
            t_n = (s[i] & 0xf) + 9;
        }
        else{
            return -1;
        }
        n_sum = n_sum * 16 + t_n;
    }
    return n_sum;
}

int utf(char* s, unsigned int code){
    int n;
    int i;

    if(code <= 0x7f){
        s[0] = code;
        return 1;
    }
    else if(code <= 0x7ff){
        n = 1;
        s[0] = (code >> 6) | 0xc0;
        code &= ~(0xff << 6);
    }
    else if(code <= 0xffff){
        n = 2;
        s[0] = (code >> 12) | 0xe0;
        code &= ~(0xff << 12);
    }
    else if(code <= 0x1fffff){
        n = 3;
        s[0] = (code >> 18) | 0xf0;
        code &= ~(0xff << 18);
    }
    else if(code <= 0x3ffffff){
        n = 4;
        s[0] = (code >> 24) | 0xf8;
        code &= ~(0xff << 24);
    }
    else if(code <= 0x7fffffff){
        n = 5;
        s[0] = (code >> 30) | 0xfc;
        code &= 0x3fffffff;
    }
    else{
        return -1;
    }
    for(i=n;i>0;i--){
        s[i] = 0x80 + (code & 0x3f);
        code >>= 6;
    }
    return n + 1;
}

struct OP* f_parse_var(char* s, int n){
    struct OP* op_1;
    struct OP* op;
    char* s_sigil;
    char char_sigil;
    char* s_index;
    int tn_len;
    char* ts_begin;
    char* ts_end;
    struct SV* sv;
    int tn_op;
    struct OP* op_var;

    if(s[1] == '{'){
        s[1] = s[0];
        return f_parse_var(s + 1, n - 3);
    }
    if(s[n-1] != '}' && s[n-1] != ']'){
        if(s[1] != '$'){
            return f_parse_var_simple(s, n);
        }
        else{
            op_1 = f_parse_var(s + 1, n - 1);
            op = get_op();
            op->type = OP_SIGIL;
            op->left.n = s[0];
            op->right.op = op_1;
            return op;
        }
    }
    s_sigil = s++;
    while(*s == '$'){
        s++;
    }
    while(isword(*s)){
        s++;
    }
    if(*s_sigil == '$'){
        if(*s == '['){
            char_sigil = '@';
        }
        else if(*s == '{'){
            char_sigil = '%';
        }
        else{
            char_sigil = '$';
        }
    }
    else{
        char_sigil = '@';
    }
    s_index = s;
    s = s_sigil;
    tn_len = (int)(s_index - s_sigil);
    if(s[1] != '$'){
        op = f_parse_var_simple(s, tn_len);
    }
    else{
        op_1 = f_parse_var(s + 1, tn_len - 1);
        op = get_op();
        op->type = OP_SIGIL;
        op->left.n = char_sigil;
        op->right.op = op_1;
    }
    s = s_index;
    while(1){
        if(*s == '[' || *s == '{'){
            ts_begin = s;
            ts_end = f_scan_delim_quick(ts_begin);
            tn_len = (int)(ts_end - ts_begin) + 1;
            if(ts_begin[1] == '$'){
                op_1 = f_parse_var(ts_begin + 1, tn_len);
            }
            else{
                if(ts_begin[1] == '\'' && ts_end[-1] == '\''){
                    sv = sv_from_s(ts_begin + 2, tn_len - 2);
                }
                else{
                    sv = sv_from_s(ts_begin + 1, tn_len);
                }
                op_1 = get_op();
                op_1->type = OP_CONST;
                op_1->right.op = NULL;
                op_1->right.sv = sv;
            }
            if(*ts_begin == '['){
                tn_op = OP_ARRAY_INDEX;
            }
            else{
                tn_op = OP_HASH_INDEX;
            }
            op_var = op;
            op = get_op();
            op->type = tn_op;
            op->left.op = op_var;
            op->right.op = op_1;
            s = ts_end + 1;
        }
        else if(s[0] == '-' && s[1] == '>' && (s[2] == '[' || s[2] == '{')){
            ts_begin = s + 2;
            ts_end = f_scan_delim_quick(ts_begin);
            tn_len = (int)(ts_end - ts_begin) + 1;
            if(ts_begin[1] == '$'){
                op_1 = f_parse_var(ts_begin + 1, tn_len);
            }
            else{
                if(ts_begin[1] == '\'' && ts_end[-1] == '\''){
                    sv = sv_from_s(ts_begin + 2, tn_len - 2);
                }
                else{
                    sv = sv_from_s(ts_begin + 1, tn_len);
                }
                op_1 = get_op();
                op_1->type = OP_CONST;
                op_1->right.op = NULL;
                op_1->right.sv = sv;
            }
            if(*ts_begin == '['){
                tn_op = OP_ARRAY_INDEX;
            }
            else{
                tn_op = OP_HASH_INDEX;
            }
            op_var = op;
            op = get_op();
            op->type = tn_op;
            op->left.op = op_var;
            op->right.op = op_1;
            s = ts_end + 1;
        }
        else{
            break;
        }
    }
    return op;
}

struct OP* f_parse_var_simple(char* s, int n){
    struct OP* op;
    char* ts_orig;
    char char_end;
    int i_var;

    op = f_parse_var_special(s[0], s + 1);
    if(op){
        return op;
    }
    ts_orig = s;
    char_end = s[n];
    s[n] = '\0';
    i_var = find_local(s);
    if(i_var){
        op = get_op();
        op->type = OP_LOCAL;
        op->left.n = *s;
        op->right.n = i_var;
    }
    else{
        i_var = find_global(s);
        if(i_var){
            op = get_op();
            op->type = OP_GLOBAL;
            op->left.n = *s;
            op->right.n = i_var;
        }
        else{
            fprintf(stderr, "string: var not found %s\n", s);
            exit(-1);
        }
    }
    ts_orig[n] = char_end;
    return op;
}

