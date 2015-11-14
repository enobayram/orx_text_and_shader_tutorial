#include <orx.h>

orxOBJECT * light_bulb;

// Now we need to keep the viewport in a global variable
orxVIEWPORT * viewport;

// This method will be called whenever Orx needs the parameters for our shader
orxSTATUS orxFASTCALL lightPosHandler(const orxEVENT *_pstEvent) {
    if(_pstEvent->eID == orxSHADER_EVENT_SET_PARAM) {
        orxSHADER_EVENT_PAYLOAD * payload = (orxSHADER_EVENT_PAYLOAD *)_pstEvent->pstPayload;
        if(strcmp(payload->zParamName, "LightPos") == 0) {
            // Here we set the "LightPos" parameter to be the mouse position
            orxMouse_GetPosition(&(payload->vValue));
            payload->vValue.fZ = 100;
        }
    }
    return orxSTATUS_SUCCESS;
}

orxSTATUS orxFASTCALL Init()
{
  viewport = orxViewport_CreateFromConfig("Viewport");
  orxObject_CreateFromConfig("TextObject");

  // Create the light bulb
  light_bulb = orxObject_CreateFromConfig("LightBulb");

  // Register our shader parameter handler
  orxEvent_AddHandler ( orxEVENT_TYPE_SHADER, lightPosHandler);
  return orxSTATUS_SUCCESS;
}

orxSTATUS orxFASTCALL Run()
{
  orxVECTOR mousePos;
  orxVECTOR mouseInWorld;

  // Get the mouse position on screen
  orxMouse_GetPosition(&mousePos);

  // Get the mouse position in the game world,
  // note that the mouse might not be in our game's window
  orxVECTOR * inWindow = orxRender_GetWorldPosition(&mousePos, viewport, &mouseInWorld);
  if(inWindow) {
    mouseInWorld.fZ = -0.1;
  } else {
    mouseInWorld.fZ = -2; // Out of camera frustum, so the light_bulb is hidden
  }
  orxObject_SetPosition(light_bulb, &mouseInWorld);

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

