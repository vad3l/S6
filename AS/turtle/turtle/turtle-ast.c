#include "turtle-ast.h"

#include <assert.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

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

/*
 *	CMD
 */

struct ast_node* make_cmd_random (struct ast_node* a, struct ast_node* b) {
	struct ast_node* node = calloc(1, sizeof(struct ast_node));
	node->kind = KIND_EXPR_FUNC;
	node->u.func = FUNC_RANDOM;
	node->children_count = 2;
	node->children[0] = a;
	node->children[1] = b;
}

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
			case CMD_LEFT:
				ctx->angle -= node->children[0]->u.value;
				break;
			case CMD_RIGHT:
				ctx->angle += node->children[0]->u.value;
				break;
			case CMD_FORWARD:
				walk(true, node, ctx);
				break;
			case CMD_BACKWARD:
				walk(false, node, ctx);
				break;
			case CMD_COLOR:
				printf("Color %f %f %f\n",node->children[0]->u.value,node->children[1]->u.value,node->children[2]->u.value);
				break;
			case CMD_POSITION:
				char *word = (!ctx->up ? "LineTo": "MoveTo") ;
				printf("%s %f %f\n",word, node->children[0]->u.value,node->children[1]->u.value );
				ctx->x += node->children[0]->u.value; ctx->y += node->children[1]->u.value;
		}
	} else if (node->kind == KIND_EXPR_FUNC) {

	}

	if (node->next != NULL) {
		ast_node_eval(node->next, ctx);
	}
}

void walk (bool forward,const struct ast_node* node, struct context* ctx) {
	double dist = (forward ? node->children[0]->u.value : -node->children[0]->u.value);
	double angle = ctx->angle * (PI/180.0);
	double dx = dist * cos(angle);
	double dy = dist * sin(angle);
	char *word = (!ctx->up ? "LineTo": "MoveTo") ;
	printf("%s %f %f\n",word, ctx->x + dx,ctx->y + dy );
	ctx->x += dx; ctx->y += dy;
}

/*
 * print
 */

void ast_print(const struct ast *self) {
}
