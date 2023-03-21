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

struct ast_node *make_expr_value(double value) {
	struct ast_node *node = calloc(1, sizeof(struct ast_node));
	node->kind = KIND_EXPR_VALUE;
	node->u.value = value;
	return node;
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
	return node;
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

struct ast_node *make_cmd_forbackward(bool choice,struct ast_node *expr) {
	struct ast_node *node = calloc(1, sizeof(struct ast_node));
	node->kind = KIND_CMD_SIMPLE;
	node->u.cmd = (choice ? CMD_FORWARD: CMD_BACKWARD);
	node->children_count = 1;
	node->children[0] = expr;
	return node;
}

struct ast_node *make_cmd_color_rgb(struct ast_node *r,struct ast_node *g,struct ast_node *b) {
	struct ast_node *node = calloc(1, sizeof(struct ast_node));
	node->kind = KIND_CMD_SIMPLE;
	node->u.cmd = CMD_COLOR;
	node->children_count = 3;

	node->children[0] = r;
	node->children[1] = g;
	node->children[2] = b;
	
	return node;
}

struct ast_node *make_cmd_color(double r,double g,double b) {
	struct ast_node *node = calloc(1, sizeof(struct ast_node));
	node->kind = KIND_CMD_SIMPLE;
	node->u.cmd = CMD_COLOR;
	node->children_count = 3;

	struct ast_node *noder = calloc(1, sizeof(struct ast_node));
	struct ast_node *nodeg = calloc(1, sizeof(struct ast_node));
	struct ast_node *nodeb = calloc(1, sizeof(struct ast_node));

	noder->u.value = r;
	nodeg->u.value = g;
	nodeb->u.value = b;

	node->children[0] = noder;
	node->children[1] = nodeg;
	node->children[2] = nodeb;
	
	return node;
}

struct ast_node *make_cmd_pencilLead(bool up) {
	struct ast_node *node = calloc(1, sizeof(struct ast_node));
	node->kind = KIND_CMD_SIMPLE;
	node->children_count = 0;
	node->u.cmd = ( up ? CMD_UP : CMD_DOWN);
	return node;
}

struct ast_node *make_cmd_rotate(bool left,struct ast_node *expr) {
	struct ast_node *node = calloc(1, sizeof(struct ast_node));
	node->kind = KIND_CMD_SIMPLE;
	node->u.cmd = (left ? CMD_LEFT: CMD_RIGHT);
	node->children_count = 1;
	node->children[0] = expr;
	return node;
}

struct ast_node *make_cmd_position(struct ast_node *expr,struct ast_node *expr1) {
	struct ast_node *node = calloc(1, sizeof(struct ast_node));
	node->kind = KIND_CMD_SIMPLE;
	node->u.cmd = CMD_POSITION;
	node->children_count = 2;
	node->children[0] = expr;
	node->children[1] = expr1;
	return node;
}

struct ast_node *make_cmd_home() {
	struct ast_node *node = calloc(1, sizeof(struct ast_node));
	node->kind = KIND_CMD_SIMPLE;
	node->children_count = 0;
	node->u.cmd = CMD_HOME;
	return node;
}

struct ast_node *make_cmd_heading(struct ast_node *expr) {
	struct ast_node *node = calloc(1, sizeof(struct ast_node));
	node->kind = KIND_CMD_SIMPLE;
	node->children_count = 1;
	node->u.cmd = CMD_HEADING;
	node->children[0] = expr;
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

void context_create(struct context *self) {
	self->x = 0.0;
	self->y = 0.0;
	self->angle = -90.0;
	self->up = false;
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

	if (node->next != NULL) {
		ast_node_eval(node->next, ctx);
	}
}

double ast_node_eval_return (const struct ast_node* n, struct context* ctx) {
	if (n->kind == KIND_EXPR_VALUE) {
		return n->u.value;
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
		case KIND_CMD_SIMPLE:
			printf("CMD_SIMPLE\n\tcmd : %i\n", n->u.cmd);
			break;
		case KIND_EXPR_FUNC:
			printf("EXPR_FUNC\n\tname : %i\n", n->u.func);
			break;
		case KIND_EXPR_VALUE:
			printf("EXPR_VALUE\n\tvalue : %f\n", n->u.value);
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
