#include <stdio.h>
#include <string.h>
#include <libxml/parser.h>

int main(int argc, char **argv) {
   xmlDoc *document;
   xmlNode *root, *first_child, *node;
   char *filename;

/*   if (argc < 2) {
     fprintf(stderr, "Usage: %s filename.xml\n", argv[0]);
     return 1;
   } */
   filename = "test.xml";

  document = xmlReadFile(filename, NULL, 0);
  root = xmlDocGetRootElement(document);
  fprintf(stdout, "Root is <%s> (%i)\n", root->name, root->type);
  first_child = root->children;
  for (node = first_child; node; node = node->next) {
     fprintf(stdout, "\t Child is <%s> (%i)\n", node->name, node->type);
  }
  fprintf(stdout, "...\n");
  return 0;
}

//  gcc -o read-xml $(xml2-config --cflags) -Wall $(xml2-config --libs) read-xml.c