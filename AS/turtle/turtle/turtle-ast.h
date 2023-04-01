#ifndef TURTLE_AST_H
#define TURTLE_AST_H

#include <stddef.h>
#include <stdbool.h>

// simple commands
enum ast_cmd {
	CMD_UP,
	CMD_DOWN,
	CMD_RIGHT,
	CMD_LEFT,
	CMD_HEADING,
	CMD_FORWARD,
	CMD_BACKWARD,
	CMD_POSITION,
	CMD_HOME,
	CMD_COLOR,
	CMD_PRINT,
};

// internal functions
enum ast_func {
	FUNC_COS,
	FUNC_RANDOM,
	FUNC_SIN,
	FUNC_SQRT,
	FUNC_TAN,
};

// kind of a node in the abstract syntax tree
enum ast_kind {
	KIND_CMD_SIMPLE,
	KIND_CMD_REPEAT,
	KIND_CMD_BLOCK,
	KIND_CMD_PROC,
	KIND_CMD_CALL,
	KIND_CMD_SET,

	KIND_EXPR_FUNC,
	KIND_EXPR_VALUE,
	KIND_EXPR_UNOP,
	KIND_EXPR_BINOP,
	KIND_EXPR_BLOCK,
	KIND_EXPR_NAME,
};

#define AST_CHILDREN_MAX 3

// a node in the abstract syntax tree
struct ast_node {
	enum ast_kind kind; // kind of the node

	union {
		enum ast_cmd cmd;	 // kind == KIND_CMD_SIMPLE
		double value;			 // kind == KIND_EXPR_VALUE, for literals
		char op;						// kind == KIND_EXPR_BINOP or kind == KIND_EXPR_UNOP, for operators in expressions
		char *name;				 // kind == KIND_EXPR_NAME, the name of procedures and variables
		enum ast_func func; // kind == KIND_EXPR_FUNC, a function
	} u;

	size_t children_count;	// the number of children of the node
	struct ast_node *children[AST_CHILDREN_MAX];	// the children of the node (arguments of commands, etc)
	struct ast_node *next;	// the next node in the sequence
};

void ast_node_destroy (struct ast_node* self);
// TODO: make some constructors to use in parser.y
// for example:
struct ast_node *make_expr_value (double value);
struct ast_node* make_expr_sin (struct ast_node* a);
struct ast_node* make_expr_cos (struct ast_node* a);
struct ast_node* make_expr_tan (struct ast_node* a);
struct ast_node* make_expr_sqrt (struct ast_node* a);
struct ast_node* make_expr_random (struct ast_node* a, struct ast_node* b);
struct ast_node* make_expr_add (struct ast_node* a, struct ast_node* b);
struct ast_node* make_expr_sub (struct ast_node* a, struct ast_node* b);
struct ast_node* make_expr_mul (struct ast_node* a, struct ast_node* b);
struct ast_node* make_expr_div (struct ast_node* a, struct ast_node* b);
struct ast_node* make_expr_unop (struct ast_node* a);
struct ast_node* make_expr_name (const char* name);
	
struct ast_node *make_cmd_rotate (bool left,struct ast_node *expr);
struct ast_node *make_cmd_forbackward (bool choice, struct ast_node *expr);
struct ast_node *make_cmd_color (double r,double g,double b);
struct ast_node *make_cmd_color_rgb (struct ast_node *r,struct ast_node *g,struct ast_node *b);
struct ast_node *make_cmd_pencilLead (bool up);
struct ast_node *make_cmd_position (struct ast_node *expr,struct ast_node *expr1);
struct ast_node *make_cmd_home ();
struct ast_node *make_cmd_heading (struct ast_node *expr);
struct ast_node *make_cmd_repeat (struct ast_node *nb,struct ast_node *expr);
struct ast_node *make_cmd_bloc (struct ast_node *expr);
struct ast_node* make_cmd_set (struct ast_node* name, struct ast_node* a);
struct ast_node* make_cmd_proc (struct ast_node* name, struct ast_node* expr);
struct ast_node* make_cmd_call (struct ast_node* name);

// root of the abstract syntax tree
struct ast {
	struct ast_node *unit;
};

// do not forget to destroy properly! no leaks allowed!
void ast_destroy(struct ast *self);

struct list_node {
	char* name;
	double value;
	struct ast_node* block;
	struct list_node* next;
};

struct list {
	struct list_node* first;
};

// the execution context
struct context {
	double x;
	double y;
	double angle;
	bool up;
	struct list* variable;
};

// create an initial context
void context_create(struct context *self);
void add_variable (struct context* self, const char* name, double value);
void add_proc (struct context* self, const char* name, struct ast_node* block);
struct ast_node* get_proc (struct context* self, const char* name);
double get_var (struct context* self, const char* name);
bool remove_name (struct context* self, const char* name);
void print_list (struct list* l);
void print_list_node (struct list_node* l);
void context_destroy (struct context* self);

// print the tree as if it was a Turtle program
void ast_node_print (const struct ast_node* self);
void ast_print(const struct ast *self);

// evaluate the tree and generate some basic primitives
void ast_eval(const struct ast *self, struct context *ctx);
void ast_node_eval (const struct ast_node *node, struct context* ctx);
double ast_node_eval_return (const struct ast_node* n, struct context* ctx);

// CMD
void position (const struct ast_node* n, struct context* ctx);
void color (const struct ast_node* n, struct context* ctx);
double random (const struct ast_node* n, struct context* ctx);
double fsin (const struct ast_node* n, struct context* ctx);
double fcos (const struct ast_node* n, struct context* ctx); 
double ftan (const struct ast_node* n, struct context* ctx);
double fsqrt (const struct ast_node* n, struct context* ctx);

void walk (bool forward,const struct ast_node* n, struct context* ctx);
void rotate (bool left,const struct ast_node* n, struct context* ctx);
void heading(struct context* ctx, int angle);
#endif /* TURTLE_AST_H */
