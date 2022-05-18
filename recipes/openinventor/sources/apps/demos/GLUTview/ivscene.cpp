#include <Inventor/SoInventor.h>
#include <iostream>

SoSeparator *readFile(const char *filename);

SoSeparator *
ivScene(const char *file)
{
   SoSeparator *root = new SoSeparator;

   root->addChild(new SoTransformerManip);
   root->addChild(new SoCone);
   
#if 0
   SoFont *font = new SoFont;
   font->name = "Arial";
   root->addChild(font);
   
   SoText2 *node = new SoText2;
   node->string = "Hallo";
   root->addChild(node);
#endif
   
   return root;
}

SoSeparator *
readFile(const char *filename)
{
   SoInput mySceneInput;
   if(!mySceneInput.openFile(filename)) {
      std::cerr << "Cannot open file "<< filename << std::endl;
      return 0;
   }

   SoSeparator *myGraph= SoDB::readAll(&mySceneInput);
   if(myGraph == 0) {
      std::cerr << "Problem reading file" << std::endl;
      return 0;
   }

   mySceneInput.closeFile();
   return myGraph;
}
