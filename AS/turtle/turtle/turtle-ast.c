#include "turtle-ast.h"

#include <assert.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>

#define PI 3.141592653589793

/*
 *	EXPR
 */

struct ast_node *make_expr_value (double value) {
	struct ast_node *node = calloc(1, sizeof(struct ast_node));
	node->kind = KIND_EXPR_VALUE;
	node->u.value = value;
	node->children_count = 0;
	return node;
}

struct ast_node* make_expr_name (const char* name) {
	struct ast_node* n = calloc(1, sizeof(struct ast_node));
	n->kind = KIND_EXPR_NAME;
	char* cpy = calloc(strlen(name) + 1, sizeof(char));
	strcpy(cpy, name);
	n->u.name = cpy;
	n->children_count = 0;
	return n;
}

struct ast_node* make_expr_unop (struct ast_node* a) {
	struct ast_node* n = calloc(1, sizeof(struct ast_node));
	n->kind = KIND_EXPR_UNOP;
	n->u.op = '-';
	n->children_count = 1;
	n->children[0] = a;
	return n;
}

struct ast_node* make_expr_add (struct ast_node* a, struct ast_node* b) {
	struct ast_node* n = calloc(1, sizeof(struct ast_node));
	n->kind = KIND_EXPR_BINOP;
	n->u.op = '+';
	n->children_count = 2;
	n->children[0] = a;
	n->children[1] = b;
	return n;
}

struct ast_node* make_expr_sub (struct ast_node* a, struct ast_node* b) {
	struct ast_node* n = calloc(1, sizeof(struct ast_node));
	n->kind = KIND_EXPR_BINOP;
	n->u.op = '-';
	n->children_count = 2;
	n->children[0] = a;
	n->children[1] = b;
	return n;
}

struct ast_node* make_expr_mul (struct ast_node* a, struct ast_node* b) {
	struct ast_node* n = calloc(1, sizeof(struct ast_node));
	n->kind = KIND_EXPR_BINOP;
	n->u.op = '*';
	n->children_count = 2;
	n->children[0] = a;
	n->children[1] = b;
	return n;
}

struct ast_node* make_expr_div (struct ast_node* a, struct ast_node* b) {
	struct ast_node* n = calloc(1, sizeof(struct ast_node));
	n->kind = KIND_EXPR_BINOP;
	n->u.op = '/';
	n->children_count = 2;
	n->children[0] = a;
	n->children[1] = b;
	return n;
}

struct ast_node* make_expr_sin (struct ast_node* a) {
	struct ast_node* node = calloc(1, sizeof(struct ast_node));
	node->kind = KIND_EXPR_FUNC;
	node->u.func = FUNC_SIN;
	node->children_count = 1;
	node->children[0] = a;
	return node;
}

struct ast_node* make_expr_cos (struct ast_node* a) {
	struct ast_node* node = calloc(1, sizeof(struct ast_node));
	node->kind = KIND_EXPR_FUNC;
	node->u.func = FUNC_COS;
	node->children_count = 1;
	node->children[0] = a;
	return node;
}

struct ast_node* make_expr_tan (struct ast_node* a) {
	struct ast_node* node = calloc(1, sizeof(struct ast_node));
	node->kind = KIND_EXPR_FUNC;
	node->u.func = FUNC_TAN;
	node->children_count = 1;
	node->children[0] = a;
	return node;
}

struct ast_node* make_expr_sqrt (struct ast_node* a) {
	struct ast_node* node = calloc(1, sizeof(struct ast_node));
	node->kind = KIND_EXPR_FUNC;
	node->u.func = FUNC_SQRT;
	node->children_count = 1;
	node->children[0] = a;
	return a->u.value < 0 ? NULL : node;
}

struct ast_node* make_expr_random (struct ast_node* a, struct ast_node* b) {
	struct ast_node* node = calloc(1, sizeof(struct ast_node));
	node->kind = KIND_EXPR_FUNC;
	node->u.func = FUNC_RANDOM;
	node->children_count = 2;
	node->children[0] = a;
	node->children[1] = b;
	return node;
}

/*
 *	CMD
 */

struct ast_node *make_cmd_forbackward (bool choice,struct ast_node *expr) {
	struct ast_node *node = calloc(1, sizeof(struct ast_node));
	node->kind = KIND_CMD_SIMPLE;
	node->u.cmd = (choice ? CMD_FORWARD: CMD_BACKWARD);
	node->children_count = 1;
	node->children[0] = expr;
	return node;
}

struct ast_node* make_cmd_set (const char* name, struct ast_node* a) {
	char* str = strtok((char*)name, " ");
	struct ast_node* n = calloc(1, sizeof(struct ast_node));
	n->kind = KIND_CMD_SET;
	char* cpy = calloc(strlen(str) + 1, sizeof(char));
	strcpy(cpy, str);
	n->u.name = cpy;
	n->children_count = 1;
	n->children[0] = a;
	return n;
}

struct ast_node *make_cmd_color_rgb (struct ast_node *r,struct ast_node *g,struct ast_node *b) {
	struct ast_node *node = calloc(1, sizeof(struct ast_node));
	node->kind = KIND_CMD_SIMPLE;
	node->u.cmd = CMD_COLOR;
	node->children_count = 3;

	node->children[0] = r;
	node->children[1] = g;
	node->children[2] = b;
	
	return node;
}

struct ast_node *make_cmd_color (double r,double g,double b) {
	struct ast_node *node = calloc(1, sizeof(struct ast_node));
	node->kind = KIND_CMD_SIMPLE;
	node->u.cmd = CMD_COLOR;
	node->children_count = 3;

	struct ast_node *noder = calloc(1, sizeof(struct ast_node));
	struct ast_node *nodeg = calloc(1, sizeof(struct ast_node));
	struct ast_node *nodeb = calloc(1, sizeof(struct ast_node));

	noder->kind = KIND_EXPR_VALUE;
	nodeb->kind = KIND_EXPR_VALUE;
	nodeg->kind = KIND_EXPR_VALUE;
	noder->u.value = r;
	nodeg->u.value = g;
	nodeb->u.value = b;

	node->children[0] = noder;
	node->children[1] = nodeg;
	node->children[2] = nodeb;
	
	return node;
}

struct ast_node *make_cmd_pencilLead (bool up) {
	struct ast_node *node = calloc(1, sizeof(struct ast_node));
	node->kind = KIND_CMD_SIMPLE;
	node->children_count = 0;
	node->u.cmd = ( up ? CMD_UP : CMD_DOWN);
	return node;
}

struct ast_node *make_cmd_rotate (bool left,struct ast_node *expr) {
	struct ast_node *node = calloc(1, sizeof(struct ast_node));
	node->kind = KIND_CMD_SIMPLE;
	node->u.cmd = (left ? CMD_LEFT: CMD_RIGHT);
	node->children_count = 1;
	node->children[0] = expr;
	return node;
}

struct ast_node *make_cmd_position (struct ast_node *expr,struct ast_node *expr1) {
	struct ast_node *node = calloc(1, sizeof(struct ast_node));
	node->kind = KIND_CMD_SIMPLE;
	node->u.cmd = CMD_POSITION;
	node->children_count = 2;
	node->children[0] = expr;
	node->children[1] = expr1;
	return node;
}

struct ast_node *make_cmd_home () {
	struct ast_node *node = calloc(1, sizeof(struct ast_node));
	node->kind = KIND_CMD_SIMPLE;
	node->children_count = 0;
	node->u.cmd = CMD_HOME;
	return node;
}

struct ast_node *make_cmd_heading (struct ast_node *expr) {
	struct ast_node *node = calloc(1, sizeof(struct ast_node));
	node->kind = KIND_CMD_SIMPLE;
	node->children_count = 1;
	node->u.cmd = CMD_HEADING;
	node->children[0] = expr;
	return node;
}

struct ast_node *make_cmd_repeat (struct ast_node *nb,struct ast_node *expr) {
	struct ast_node *node = calloc(1, sizeof(struct ast_node));
	node->kind = KIND_CMD_REPEAT;
	node->children_count = 2;
	node->children[0] = nb;
	node->children[1] = expr;
	return node;
}

struct ast_node *make_cmd_bloc (struct ast_node *expr) {
	struct ast_node *node = calloc(1, sizeof(struct ast_node));
	node->kind = KIND_CMD_BLOCK;
	node->children_count = 1;
	node->children[0] = expr;
	return node;
}

struct ast_node* make_cmd_proc (const char* name, struct ast_node* expr) {
	struct ast_node *node = calloc(1, sizeof(struct ast_node));
	node->kind = KIND_CMD_PROC;
	node->u.name = calloc(strlen(name) + 1, sizeof(char));
	strcpy(node->u.name,name);
	node->children_count = 1;
	node->children[0] = expr;
	return node;
}

struct ast_node* make_cmd_call (const char* name) {
	struct ast_node *node = calloc(1, sizeof(struct ast_node));
	node->kind = KIND_CMD_CALL;
	node->u.name = calloc(strlen(name) + 1, sizeof(char));
	strcpy(node->u.name,name);
	return node;
}

/*
 *	AST
 */

void ast_node_destroy (struct ast_node* self) {
	if (self == NULL){return ;}
	for (size_t i = 0; i < self->children_count; i++) {
		if (self->children[i] != NULL) {
			ast_node_destroy(self->children[i]);
		}
	}
	if (self->next != NULL) {
		ast_node_destroy(self->next);
	}
	free(self);
}

void ast_destroy(struct ast *self) {
	if (self == NULL){return ;}
	ast_node_destroy(self->unit);
}

/*
 * context
 */

void list_node_destroy(struct list_node* n) {
	free((void *)n->name);
	free(n->block);
	free(n);
}

void context_create(struct context *self) {
	self->x = 0.0;
	self->y = 0.0;
	self->angle = -90.0;
	self->up = false;
	self->variable = calloc(1, sizeof(struct list));
	self->variable->first = NULL;
}

void context_destroy (struct context* self) {
	struct list_node* v = self->variable->first;
	while (v != NULL) {
		struct list_node* c = v;
		v = v->next;
		list_node_destroy(c);
	}
	free(self->variable);
}

void add_variable (struct context* self, const char* name, double value) {
	struct list_node* node = calloc(1, sizeof(struct list_node));
	node->value = value;
	char* cpy = calloc(strlen(name) + 1, sizeof(char));
	strcpy(cpy, name);
	node->name = cpy;
	node->block = NULL;
	node->next = NULL;
	if (self->variable->first == NULL) {
		self->variable->first = node;
		return;
	}
	struct list_node* last = self->variable->first;
	while (last->next != NULL) {
		last = last->next;
	}
	last->next = node;
}

void add_proc (struct context* self, const char* name, struct ast_node* block) {
	struct list_node* node = calloc(1, sizeof(struct list_node));
	node->block = block;
	char* cpy = calloc(strlen(name) + 1, sizeof(char));
	strcpy(cpy, name);
	node->name = cpy;
	node->block = NULL;
	node->next = NULL;
	if (self->variable->first == NULL) {
		self->variable->first = node;
		return;
	}
	struct list_node* last = self->variable->first;
	while (last->next != NULL) {
		last = last->next;
	}
	last->next = node;
}

struct ast_node* get_proc (struct context* self, const char* name) {
	struct list_node* v = self->variable->first;
	while (v != NULL) {
		printf("%s\n",v->name);
		if (strcmp(v->name, name) == 0) {
			return v->block;
		}
		v = v->next;
	}
	exit(-1);
}

double get_var (struct context* self, const char* name) {
	struct list_node* v = self->variable->first;
	while (v != NULL) {
		if (strcmp(v->name, name) == 0) {
			return v->value;
		}
		v = v->next;
	}
	exit(-1);
}

bool remove_name (struct context* self, const char* name) {
	struct list_node* prev = NULL;
	struct list_node* v = self->variable->first;
	if (v == NULL) { return false; }
	while (v != NULL) {
		if (strcmp(v->name, name) == 0) {
			if (prev == NULL) {
				self->variable->first = v->next;
				list_node_destroy(v);
				return true;
			} else {
				prev->next = v->next;
				list_node_destroy(v);
				return true;
			}
		}
		prev = v;
		v = v->next;
	}
	return false;
}

/*
 * eval
 */

void ast_eval(const struct ast *self, struct context *ctx) {
	ast_node_eval(self->unit, ctx);
}

void ast_node_eval (const struct ast_node* node, struct context *ctx) {
	if (node->kind == KIND_CMD_SIMPLE) {
		switch (node->u.cmd) {
			case CMD_UP:
				ctx->up = true;
				break;
			case CMD_DOWN:
				ctx->up = false;
				break;
			case CMD_RIGHT:
				ctx->angle += ast_node_eval_return(node->children[0], ctx);
				break;
			case CMD_LEFT:
				ctx->angle -= ast_node_eval_return(node->children[0], ctx);
				break;
			case CMD_HEADING:
				heading(ctx, ast_node_eval_return(node->children[0], ctx));
				break;
			case CMD_FORWARD:
				walk(true, node, ctx);
				break;
			case CMD_BACKWARD:
				walk(false, node, ctx);
				break;
			case CMD_POSITION:
				position(node, ctx);
				break;
			case CMD_HOME:
				context_create(ctx);
				break;
			case CMD_COLOR:
				color(node, ctx);
				break;
		}
	}

	if (node->kind == KIND_CMD_SET) {
		add_variable(ctx, node->u.name, ast_node_eval_return(node->children[0], ctx));
	}

	if (node->kind == KIND_CMD_REPEAT) {
		for (int i = 0 ; i < node->children[0]->u.value ; i++) {
			ast_node_eval(node->children[1],ctx);
		}
	}
	if (node->kind == KIND_CMD_BLOCK) {
		ast_node_eval(node->children[0],ctx);
	}
	if (node->kind == KIND_CMD_PROC) {
		add_proc(ctx, node->u.name, node->children[0]);
	}

	if (node->kind == KIND_CMD_CALL) {
		ast_node_eval(get_proc(ctx,node->u.name),ctx);
	}

	if (node->next != NULL) {
		ast_node_eval(node->next, ctx);
	}
}

double ast_node_eval_return (const struct ast_node* n, struct context* ctx) {
	if (n->kind == KIND_EXPR_VALUE) {
		return n->u.value;
	}
	if (n->kind == KIND_EXPR_NAME) {
		return get_var(ctx, n->u.name);
	}
	if (n->kind == KIND_EXPR_FUNC) {
		switch (n->u.func) {
			case FUNC_RANDOM:
				return random(n, ctx);
			case FUNC_SIN:
				return fsin(n, ctx);
			case FUNC_COS:
				return fcos(n, ctx);
			case FUNC_TAN:
				return ftan(n, ctx);
			case FUNC_SQRT:
				return fsqrt(n, ctx);
		}
	} else if (n->kind == KIND_EXPR_BINOP) {
		switch (n->u.op) {
			case '+':
				return ast_node_eval_return(n->children[0], ctx) + ast_node_eval_return(n->children[1], ctx);
			case '-':
				return ast_node_eval_return(n->children[0], ctx) - ast_node_eval_return(n->children[1], ctx);
			case '*':
				return ast_node_eval_return(n->children[0], ctx) * ast_node_eval_return(n->children[1], ctx);
			case '/':
				return ast_node_eval_return(n->children[0], ctx) / ast_node_eval_return(n->children[1], ctx);
		}
	} else if (n->kind == KIND_EXPR_UNOP) {
		return -ast_node_eval_return(n->children[0], ctx);
	}

	return 0.0;
}

double random (const struct ast_node* n, struct context* ctx) {
	double min = ast_node_eval_return(n->children[0], ctx);
	double max = ast_node_eval_return(n->children[1], ctx);
	double value = (((double)rand() / INT_MAX) * (max - min)) + min;
	return value;
}

double fsin (const struct ast_node* n, struct context* ctx) {
	return sin(ast_node_eval_return(n->children[0], ctx));
}
double fcos (const struct ast_node* n, struct context* ctx) {
	return cos(ast_node_eval_return(n->children[0], ctx));
}
double ftan (const struct ast_node* n, struct context* ctx) {
	return tan(ast_node_eval_return(n->children[0], ctx));
}
double fsqrt (const struct ast_node* n, struct context* ctx) {
	return sqrt(ast_node_eval_return(n->children[0], ctx));
}


void position (const struct ast_node* n, struct context* ctx) {
	if (!ctx->up) {
		printf("LineTo ");
	} else {
		printf("MoveTo ");
	}

	double a = ast_node_eval_return(n->children[0], ctx);
	double b = ast_node_eval_return(n->children[1], ctx);
	printf("%f %f\n", a, b);
	ctx->x += a;
	ctx->y += b;
}

void color (const struct ast_node* n, struct context* ctx) {
	double r = ast_node_eval_return(n->children[0], ctx);
	double g = ast_node_eval_return(n->children[1], ctx);
	double b = ast_node_eval_return(n->children[2], ctx);
	printf("Color %f %f %f\n", r, g, b);
}

void walk (bool forward,const struct ast_node* node, struct context* ctx) {
	double value = ast_node_eval_return(node->children[0], ctx);
	double dist = (forward ? value : -value);
	double angle = ctx->angle * (PI/180.0);
	double dx = dist * cos(angle);
	double dy = dist * sin(angle);
	char *word = (!ctx->up ? "LineTo": "MoveTo") ;
	printf("%s %f %f\n",word, ctx->x + dx,ctx->y + dy );
	ctx->x += dx; ctx->y += dy;
}


void heading(struct context* ctx,int angle) {
    double orientation = angle % 360;
    if (orientation < 0) {
        orientation += 360;
    }
	ctx->angle += orientation;
}

/*
 * print
 */

void ast_node_print (const struct ast_node* n) {
	switch (n->kind) {
		case KIND_CMD_CALL:
			printf("CMD_CALL\n\tname : %s\n", n->u.name);
			break;
		case KIND_CMD_SIMPLE:
			printf("CMD_SIMPLE\n\tcmd : %i\n", n->u.cmd);
			break;
		case KIND_CMD_SET:
			printf("CMD_SET\n\tname : %s\n", n->u.name);
			break;
		case KIND_EXPR_FUNC:
			printf("EXPR_FUNC\n\tname : %i\n", n->u.func);
			break;
		case KIND_EXPR_VALUE:
			printf("EXPR_VALUE\n\tvalue : %f\n", n->u.value);
			break;
		case KIND_EXPR_NAME:
			printf("EXPR NAME\n\tname : %s\n", n->u.name);
			break;
	}
	if (n->children_count > 0) {
		printf("(\n");
	}
	for (size_t i = 0; i < n->children_count; i++) {
		ast_node_print(n->children[i]);
	}
	if (n->children_count > 0) {
		printf(")\n");
	}
	if (n->next != NULL) {
		ast_node_print(n->next);
	}
}

void ast_print(const struct ast *self) {
	ast_node_print(self->unit);
}
