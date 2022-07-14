# Install script for directory: D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/cegui")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/build/lib/CEGUIBase-0_d.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/build/lib/CEGUIBase-0.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/build/lib/CEGUIBase-0.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/build/lib/CEGUIBase-0.lib")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/build/bin/CEGUIBase-0_d.dll")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/build/bin/CEGUIBase-0.dll")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/build/bin/CEGUIBase-0.dll")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/build/bin/CEGUIBase-0.dll")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/cegui-0/CEGUI" TYPE FILE FILES
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/Affector.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/Animation.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/AnimationInstance.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/AnimationManager.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/Animation_xmlHandler.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/Base.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/BasicImage.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/BasicRenderedStringParser.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/BidiVisualMapping.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/BoundSlot.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/CEGUI.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/CentredRenderedString.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/ChainedXMLHandler.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/Clipboard.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/Colour.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/ColourRect.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/CompositeResourceProvider.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/Config.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/Config_xmlHandler.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/CoordConverter.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/DataContainer.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/DefaultLogger.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/DefaultRenderedStringParser.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/DefaultResourceProvider.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/DynamicModule.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/Element.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/Event.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/EventArgs.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/EventSet.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/Exceptions.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/FactoryModule.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/FactoryRegisterer.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/Font.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/FontGlyph.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/FontManager.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/Font_xmlHandler.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/FormattedRenderedString.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/ForwardRefs.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/FreeFunctionSlot.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/FreeTypeFont.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/FribidiVisualMapping.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/FunctorCopySlot.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/FunctorPointerSlot.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/FunctorReferenceBinder.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/FunctorReferenceSlot.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/GUIContext.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/GUILayout_xmlHandler.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/GeometryBuffer.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/GlobalEventSet.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/IconvStringTranscoder.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/Image.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/ImageCodec.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/ImageFactory.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/ImageManager.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/InjectedInputReceiver.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/InputEvent.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/Interpolator.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/IteratorBase.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/JustifiedRenderedString.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/KeyFrame.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/LeftAlignedRenderedString.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/LinkedEvent.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/Logger.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/MemberFunctionSlot.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/MemoryAllocatedObject.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/MemoryAllocation.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/MemoryOgreAllocator.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/MemorySTLWrapper.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/MemoryStdAllocator.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/MinibidiVisualMapping.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/MinizipResourceProvider.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/ModuleConfig.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/MouseCursor.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/NamedElement.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/NamedXMLResourceManager.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/PCRERegexMatcher.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/PixmapFont.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/Property.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/PropertyHelper.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/PropertySet.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/Quaternion.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/Rect.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/RefCounted.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/RegexMatcher.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/RenderEffect.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/RenderEffectFactory.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/RenderEffectManager.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/RenderQueue.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/RenderTarget.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/RenderedString.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/RenderedStringComponent.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/RenderedStringImageComponent.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/RenderedStringParser.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/RenderedStringTextComponent.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/RenderedStringWidgetComponent.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/RenderedStringWordWrapper.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/Renderer.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/RenderingContext.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/RenderingSurface.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/RenderingWindow.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/ResourceProvider.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/RightAlignedRenderedString.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/Scheme.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/SchemeManager.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/Scheme_xmlHandler.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/ScriptModule.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/SimpleTimer.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/Singleton.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/Size.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/SlotFunctorBase.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/String.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/StringTranscoder.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/SubscriberSlot.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/System.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/SystemKeys.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/TextUtils.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/Texture.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/TextureTarget.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/TplInterpolators.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/TplProperty.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/TplWRFactoryRegisterer.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/TplWindowFactory.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/TplWindowFactoryRegisterer.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/TplWindowProperty.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/TplWindowRendererFactory.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/TplWindowRendererProperty.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/TypedProperty.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/UDim.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/Vector.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/Version.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/Vertex.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/Win32StringTranscoder.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/Window.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/WindowFactory.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/WindowFactoryManager.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/WindowManager.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/WindowRenderer.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/WindowRendererManager.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/XMLAttributes.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/XMLHandler.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/XMLParser.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/XMLSerializer.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/build/cegui/src/../include/CEGUI/Config.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/build/cegui/src/../include/CEGUI/ModuleConfig.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/build/cegui/src/../include/CEGUI/Version.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/cegui-0/CEGUI/widgets" TYPE FILE FILES
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/widgets/All.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/widgets/ButtonBase.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/widgets/ClippedContainer.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/widgets/ComboDropList.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/widgets/Combobox.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/widgets/DefaultWindow.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/widgets/DragContainer.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/widgets/Editbox.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/widgets/FrameWindow.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/widgets/GridLayoutContainer.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/widgets/GroupBox.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/widgets/HorizontalLayoutContainer.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/widgets/ItemEntry.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/widgets/ItemListBase.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/widgets/ItemListbox.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/widgets/LayoutCell.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/widgets/LayoutContainer.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/widgets/ListHeader.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/widgets/ListHeaderSegment.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/widgets/Listbox.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/widgets/ListboxItem.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/widgets/ListboxTextItem.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/widgets/MenuBase.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/widgets/MenuItem.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/widgets/Menubar.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/widgets/MultiColumnList.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/widgets/MultiLineEditbox.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/widgets/PopupMenu.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/widgets/ProgressBar.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/widgets/PushButton.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/widgets/RadioButton.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/widgets/ScrollablePane.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/widgets/Scrollbar.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/widgets/ScrolledContainer.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/widgets/ScrolledItemListBase.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/widgets/SequentialLayoutContainer.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/widgets/Slider.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/widgets/Spinner.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/widgets/TabButton.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/widgets/TabControl.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/widgets/Thumb.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/widgets/Titlebar.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/widgets/ToggleButton.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/widgets/Tooltip.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/widgets/Tree.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/widgets/TreeItem.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/widgets/VerticalLayoutContainer.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/cegui-0/CEGUI/falagard" TYPE FILE FILES
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/falagard/ComponentBase.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/falagard/Dimensions.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/falagard/Enums.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/falagard/EventAction.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/falagard/EventLinkDefinition.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/falagard/FalagardPropertyBase.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/falagard/FormattingSetting.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/falagard/FrameComponent.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/falagard/ImageryComponent.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/falagard/ImagerySection.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/falagard/LayerSpecification.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/falagard/NamedArea.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/falagard/NamedDefinitionCollator.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/falagard/PropertyDefinition.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/falagard/PropertyDefinitionBase.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/falagard/PropertyInitialiser.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/falagard/PropertyLinkDefinition.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/falagard/SectionSpecification.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/falagard/StateImagery.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/falagard/TextComponent.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/falagard/WidgetComponent.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/falagard/WidgetLookFeel.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/falagard/WidgetLookManager.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/falagard/XMLEnumHelper.h"
    "D:/Universidad/5 Quinto/2.Proyecto3/Github/Proyecto-3/WeirdEngine/Dependencias/cegui/cegui/src/../include/CEGUI/falagard/XMLHandler.h"
    )
endif()

