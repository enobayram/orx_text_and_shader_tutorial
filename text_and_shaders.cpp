#include <orx.h>

orxSTATUS orxFASTCALL Init()
{
  orxViewport_CreateFromConfig("Viewport");
  orxObject_CreateFromConfig("TextObject");
  return orxSTATUS_SUCCESS;
}

orxSTATUS orxFASTCALL Run()
{
  return orxSTATUS_SUCCESS;
}

void orxFASTCALL Exit()
{
}

int main(int argc, char **argv)
{
  orx_Execute(argc, argv, Init, Run, Exit);

  return EXIT_SUCCESS;
}

