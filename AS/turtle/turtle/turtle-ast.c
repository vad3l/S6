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

void ast_node_destroy (struct ast_node* self) {
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
	ast_node_destroy(self->unit);
	free(self);
}

/*
 * context
 */

void context_create(struct context *self) {
	struct context *ctx = calloc(1, sizeof(struct context));
	ctx->x = 0.0;
	ctx->y = 0.0;
	ctx->angle = 0.0;
	ctx->up = true;
}

/*
 * eval
 */

void ast_eval(const struct ast *self, struct context *ctx) {
	ast_node_eval(self->unit, ctx);
}

void ast_node_eval (const struct ast_node* node, struct context* ctx) {
	if (node->kind == KIND_CMD_SIMPLE) {
		switch (node->u.cmd) {
			case CMD_FORWARD:
				foward(node, ctx);
				break;
			case CMD_BACKWARD:
				backward(node, ctx);
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
	printf("feur\n");
}

void foward (const struct ast_node* n, struct context* ctx) {
	double new_x = ctx->x;
	double new_y = ctx->y - n->u.value;
	new_x = new_x * cos(ctx->angle) - new_y * sin(ctx->angle);
	new_y = new_x * sin(ctx->angle) + new_y * cos(ctx->angle);
	ctx->x = new_x;
	ctx->y = new_y;	
}

void backward (const struct ast_node* n, struct context* ctx) {
	double new_x = ctx->x;
	double new_y = ctx->y + n->u.value;
	new_x = new_x * cos(ctx->angle) - new_y * sin(ctx->angle);
	new_y = new_x * sin(ctx->angle) + new_y * cos(ctx->angle);
	ctx->x = new_x;
	ctx->y = new_y;	
}
