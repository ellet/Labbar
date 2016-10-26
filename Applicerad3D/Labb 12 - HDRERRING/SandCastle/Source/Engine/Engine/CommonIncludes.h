#pragma once

#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dcompiler.lib")
#pragma comment( lib, "dxguid.lib")

#include "Utilities/CommonIncludes.h"
#include "../ModelLoader/CommonIncludes.h"
#include "Engine\DataParser\DataParser.h"
namespace ENGINE_NAMESPACE {
	class BaseComponent;
}
#include "Engine\Component\ComponentPtr.h"
#include "Engine\GameObject\ObjectPtr.h"
#include "Engine\GameObject\ObjectEventSystem\EventSubscriber.h"
#include "Engine\Component\Factory\ComponentFactory.h"
#include "Engine\GameObject\GameObject.h"
#include "Engine\Component\ComponentRegistration.h"

#include "Engine\Time\Time.h"
#include <Utilities\UniqeIdentifier.h>
#include "Engine\Component\BaseComponent.h"
#include <Utilities\Container\GrowingArray.h>
#include "Engine\BoundingBox.h"
#include "Engine\Time\Stopwatch.h"
#include "Engine\PostMaster.h"

#include "Engine\Resources\ResourceManager.h"
#include "Engine\Scripting\ScriptLoader.h"
#include "Engine\Texture\TextureLoader.h"
#include "Engine\Effect\ShaderFileLoader.h"
#include "Engine\Model\AssimpModelLoader.h"

#include "Engine\Debugging\DebugLogger.h"
#include "Engine\Input\MouseButton.h"
#include "Engine\Input\MouseMessages.h"
#include "Engine\Input\KeyboardKey.h"
#include "Engine\Input\KeyMessages.h"
#include "Engine\Texture\Texture.h"
#include "Engine\Engine.h"
#include "Engine\Buffer\Buffer.h"
#include "Engine\Buffer\ConstantBuffer.h"
#include "Engine\Buffer\DepthBuffer.h"
#include "Engine\Buffer\ShaderResourceBuffer.h"
#include "Engine\Rendering\DXRenderer.h"
#include "Engine\Rendering\ModelRenderer.h"
#include "Engine\Effect\InputLayout.h"
#include "Engine\Effect\Effect.h"
#include "Engine\Model\Mesh.h"
#include "Engine\Model\Model.h"
#include "Engine\Sprite\Sprite.h"
#include "Engine\Debugging\Debugger.h"

#include "Engine\Component\ComponentPtr.h"
#include "Engine/GameObject/ObjectEventSystem/EventSubscriber.h"
#include "Engine\Scene\Scene.h"
#include "Engine\Scripting\LuaComponent.h"
#include "Engine\Component\BaseComponent.h"

