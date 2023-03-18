#include "turtle-ast.h"

#include <assert.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define PI 3.141592653589793

struct ast_node *make_expr_value(double value) {
	struct ast_node *node = calloc(1, sizeof(struct ast_node));
	node->kind = KIND_EXPR_VALUE;
	node->u.value = value;
	return node;
}

struct ast_node *make_cmd_forbackward(bool choice,struct ast_node *expr) {
	struct ast_node *node = calloc(1, sizeof(struct ast_node));
	node->kind = KIND_CMD_SIMPLE;
	node->u.cmd = (choice ? CMD_FORWARD: CMD_BACKWARD);
	node->children_count = 1;
	node->children[0] = expr;
	return node;
}

struct ast_node *make_cmd_color(struct ast_node *expr1,struct ast_node *expr2,struct ast_node *expr3) {
	struct ast_node *node = calloc(1, sizeof(struct ast_node));
	node->kind = KIND_CMD_SIMPLE;
	node->u.cmd = CMD_COLOR;
	node->children_count = 3;
	node->children[0] = expr1;
	node->children[1] = expr2;
	node->children[2] = expr3;
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
			case CMD_LEFT:
				ctx->angle -= node->children[0]->u.value;
				break;
			case CMD_RIGHT:
				ctx->angle += node->children[0]->u.value;
				break;
			case CMD_FORWARD:
				foward(node, ctx);
				break;
			case CMD_BACKWARD:
				backward(node, ctx);
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

/*
 * print
 */

void ast_print(const struct ast *self) {
	printf(":)\n");
}

void color (const struct ast_node* node, struct context* ctx) {
	printf("Color %f\n", node->children[0]->u.value );
}

void foward (const struct ast_node* node, struct context* ctx) {
	double dist = node->children[0]->u.value;
	double angle = ctx->angle * (PI/180.0);
	double dx = dist * cos(angle);
	double dy = dist * sin(angle);
	if (!ctx->up) {
		printf("LineTo %f %f\n", ctx->x + dx,ctx->y + dy );
	} else {
		printf("MoveTo %f %f\n", ctx->y + dy, ctx->x - dx);
	}
	ctx->x -= dx;
	ctx->y += dy;
}

void backward(const struct ast_node* node, struct context* ctx) {
	double dist = node->children[0]->u.value;
	double angle = ctx->angle * (PI / 180.0);
	double dx = -dist * cos(angle);
	double dy = -dist * sin(angle);
	if (!ctx->up) {
		printf("LineTo %f %f\n", ctx->x + dx, ctx->y + dy);
	}
	else {
		printf("MoveTo %f %f\n", ctx->x, ctx->y);
	}
	ctx->x += dx;
	ctx->y += dy;
}
