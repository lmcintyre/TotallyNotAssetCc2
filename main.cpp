
#include <iostream>
#include <cstdio>

#include <Common/Base/hkBase.h>
#include <Common/Base/Memory/System/Util/hkMemoryInitUtil.h>
#include <Common/Base/System/Io/IStream/hkIStream.h>
#include <Common/Base/Reflection/Registry/hkDefaultClassNameRegistry.h>
#include <Common/Serialize/Util/hkRootLevelContainer.h>
#include <Common/Serialize/Util/hkLoader.h>
#include <Common/Serialize/Util/hkSerializeUtil.h>
#include <Common/Serialize/Version/hkVersionPatchManager.h>
#include <Common/Base/Reflection/hkInternalClassMember.h>
#include <Common/Serialize/Util/hkSerializeDeprecated.h>

#include "Common/Base/System/Init/PlatformInit.cxx"

static void HK_CALL errorReport(const char* msg, void* userContext)
{
    using namespace std;
    printf("%s", msg);
}

int main(int argc, const char** argv) {
    hkStringBuf sklb;
    hkStringBuf xml;

    if (argc < 3)
        return 1;
    
    sklb = argv[1];
    xml = argv[2];

    PlatformInit();
    hkMemoryRouter* memoryRouter = hkMemoryInitUtil::initDefault( hkMallocAllocator::m_defaultMallocAllocator, hkMemorySystem::FrameInfo(1024 * 1024) );
    hkBaseSystem::init( memoryRouter, errorReport );
    PlatformFileSystemInit();
    hkSerializeDeprecatedInit::initDeprecated();

    auto loader = new hkLoader();
    hkRootLevelContainer* container = loader->load(sklb.cString());

    hkOstream stream(xml);
    hkPackfileWriter::Options packOptions;
    hkSerializeUtil::ErrorDetails errOut;

    hkResult res = hkSerializeDeprecated::getInstance().saveXmlPackfile(container, hkRootLevelContainer::staticClass(), stream.getStreamWriter(), packOptions, HK_NULL, &errOut);

    if (res.m_enum == hkResultEnum::HK_SUCCESS) {
        hkBaseSystem::quit();
        hkMemoryInitUtil::quit();
        return 0;
    } else {
        std::cout << "\n\nAn error occurred while saving the XML...\n";
        std::cout << errOut.defaultMessage << "\n";
        return 1;
    }
}

#include <Common/Base/keycode.cxx>

#undef HK_FEATURE_PRODUCT_AI
//#undef HK_FEATURE_PRODUCT_ANIMATION
#undef HK_FEATURE_PRODUCT_CLOTH
#undef HK_FEATURE_PRODUCT_DESTRUCTION_2012
#undef HK_FEATURE_PRODUCT_DESTRUCTION
#undef HK_FEATURE_PRODUCT_BEHAVIOR
#undef HK_FEATURE_PRODUCT_PHYSICS_2012
#undef HK_FEATURE_PRODUCT_SIMULATION
#undef HK_FEATURE_PRODUCT_PHYSICS

#define HK_SERIALIZE_MIN_COMPATIBLE_VERSION 201130r1

#include <Common/Base/Config/hkProductFeatures.cxx>