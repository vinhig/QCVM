/*******************************************************************************
 *
 * MIT License
 *
 * Copyright (c) 2023 erysdren (it/she)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 * 
 ******************************************************************************/

/*
 * headers
 */

/* std */
#include <stdio.h>
#include <string.h>

/* qcvm */
#include "qcvm_private.h"

/*
 * exports
 */

/* add export */
void qcvm_add_export(qcvm_t *qcvm, qcvm_export_t export)
{
	qcvm->exports[qcvm->num_exports] = export;
	qcvm->num_exports++;
}

/* dump exports to properly formatted qc */
void qcvm_dump_exports(qcvm_t *qcvm, const char *filename)
{
	/* variables */
	FILE *file;
	int i, a;

	/* open file */
	file = fopen(filename, "wb");
	if (file == NULL) return;

	/* write exports */
	for (i = 0; i < qcvm->num_exports; i++)
	{
		/* return type */
		switch (qcvm->exports[i].type)
		{
			/* valid return types */
			case QCVM_VOID: fprintf(file, "void"); break;
			case QCVM_FLOAT: fprintf(file, "float"); break;
			case QCVM_INT: fprintf(file, "int"); break;
			case QCVM_ENTITY: fprintf(file, "entity"); break;
			case QCVM_STRING: fprintf(file, "string"); break;
			case QCVM_VECTOR: fprintf(file, "vector"); break;

			/* invalid return value */
			case QCVM_VARGS:
			default:
				fprintf(stderr, "error: invalid return type\n");
				return;
		}

		/* function name */
		fprintf(file, " %s(", qcvm->exports[i].name);

		/* write args */
		for (a = 0; a < qcvm->exports[i].argc; a++)
		{
			/* write comma */
			if (a > 0 && a < 7) fprintf(file, ", ");

			/* check for vargs */
			if (qcvm->exports[i].args[a].type == QCVM_VARGS)
			{
				fprintf(file, "...");
				break;
			}

			/* arg type */
			switch (qcvm->exports[i].args[a].type)
			{
				/* valid arg types */
				case QCVM_VOID: fprintf(file, "void"); break;
				case QCVM_FLOAT: fprintf(file, "float"); break;
				case QCVM_INT: fprintf(file, "int"); break;
				case QCVM_ENTITY: fprintf(file, "entity"); break;
				case QCVM_STRING: fprintf(file, "string"); break;
				case QCVM_VECTOR: fprintf(file, "vector"); break;

				/* invalid return value */
				default:
					fprintf(stderr, "error: invalid return type\n");
					return;
			}

			/* write arg name */
			fprintf(file, " %s", qcvm->exports[i].args[a].name);
		}

		/* write ending chunk */
		fprintf(file, ") = #0 : %s;\n", qcvm->exports[i].name);
	}

	/* close file */
	fclose(file);
}
