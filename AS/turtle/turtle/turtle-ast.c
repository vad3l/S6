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

struct ast_node *make_cmd_forbackward(bool choice,struct ast_node *expr) {
	struct ast_node *node = calloc(1, sizeof(struct ast_node));
	node->kind = KIND_CMD_SIMPLE;
	node->u.cmd = (choice ? CMD_FORWARD: CMD_BACKWARD);
	node->children_count = 1;
	node->children[0] = expr;
	return node;
}

struct ast_node *make_cmd_color(struct ast_node *expr) {
	struct ast_node *node = calloc(1, sizeof(struct ast_node));
	node->kind = KIND_CMD_SIMPLE;
	node->u.cmd = CMD_COLOR;
	node->children_count = 3;

	struct ast_node *r = calloc(1, sizeof(struct ast_node));
	struct ast_node *g = calloc(1, sizeof(struct ast_node));
	struct ast_node *b = calloc(1, sizeof(struct ast_node));

	if (strcmp(expr->u.name,"red") == 0) { r->u.value = 1.0; }
	else if (strcmp(expr->u.name,"green") == 0) { g->u.value = 1.0; }
	else if (strcmp(expr->u.name,"blue") == 0) { b->u.value = 1.0; }
	else if (strcmp(expr->u.name,"cyan") == 0) { g->u.value = 1.0; b->u.value = 1.0; }
	else if (strcmp(expr->u.name,"magenta") == 0) { r->u.value = 1.0; b->u.value = 1.0; }
	else if (strcmp(expr->u.name,"yellow") == 0) { r->u.value = 1.0; g->u.value = 1.0; }
	else if (strcmp(expr->u.name,"black") == 0) { }
	else if (strcmp(expr->u.name,"gray") == 0) { r->u.value = 0.5; g->u.value = 0.5; b->u.value = 0.5; }
	else if (strcmp(expr->u.name,"white") == 0) { r->u.value = 1.0; g->u.value = 1.0; b->u.value = 1.0; }
	else { r->u.value = atof(strtok(expr->u.name, ", ")); g->u.value = atof(strtok(NULL, ", ")); b->u.value = atof(strtok(NULL, ", "));}
	node->children[0] = r;
	node->children[1] = g;
	node->children[2] = b;
	
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
				walk(true, node, ctx);
				break;
			case CMD_BACKWARD:
				walk(false, node, ctx);
				break;
			case CMD_COLOR:
				printf("Color %f %f %f\n",node->children[0]->u.value,node->children[1]->u.value,node->children[2]->u.value);
				break;
		}
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
	if (!ctx->up) {
		printf("LineTo %f %f\n", ctx->x + dx,ctx->y + dy );
	} else {
		printf("MoveTo %f %f\n", ctx->y + dy, ctx->x - dx);
	}
	ctx->x += dx;
	ctx->y += dy;
}

/*
 * print
 */

void ast_print(const struct ast *self) {
}