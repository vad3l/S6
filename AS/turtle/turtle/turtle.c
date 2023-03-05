#include <assert.h>
#include <stdlib.h>
#include <time.h>

#include "turtle-ast.h"
#include "turtle-lexer.h"
#include "turtle-parser.h"

int main() {
	srand(time(NULL));

	struct ast root;
	int ret = yyparse(&root);

	if (ret != 0) {
		return ret;
	}

	yylex_destroy();

	assert(root.unit);

	struct context ctx;
	context_create(&ctx);

	ast_eval(&root, &ctx);
//	 ast_print(&root);

	ast_destroy(&root);

	return ret;
}


struct ast_node *make_cmd_forward(struct ast_node *expr) {
	struct ast_node *node = calloc(1, sizeof(struct ast_node));
	node->kind = KIND_CMD_SIMPLE;
	node->u.cmd = CMD_FORWARD;
	node->children_count = 1;
	node->children[0] = expr;
	return node;
}