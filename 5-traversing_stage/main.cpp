#include <iostream>

#include <pxr/usd/usd/stage.h>
#include <pxr/usd/usd/primRange.h>
#include <pxr/usd/usdGeom/xform.h>
#include <pxr/usd/usdGeom/sphere.h>
#include <pxr/usd/usdGeom/xformCommonAPI.h>
#include <pxr/usd/sdf/layer.h>

int main() {
    // create a new stage
    auto stage = pxr::UsdStage::CreateNew("helloworld.usda");
    auto xform = stage->DefinePrim(pxr::SdfPath("/hello"), pxr::TfToken("Xform"));
    auto sphere = stage->DefinePrim(pxr::SdfPath("/hello/world"), pxr::TfToken("Sphere"));

    // set default prim & translate xform
    stage->SetDefaultPrim(xform);
    pxr::UsdGeomXformCommonAPI(xform).SetTranslate({4, 5, 6});
    stage->GetRootLayer()->Save();

    std::cout << "to ref usd:" << std::endl;
    std::string result;
    stage->GetRootLayer()->ExportToString(&result);
    std::cout << result << std::endl;

    // traverse stage
    // ref from usd-cookbook
    auto range = pxr::UsdPrimRange::Stage(stage);
    std::for_each(std::begin(range), std::end(range),[](pxr::UsdPrim const &prim){
        std::cout << "do something to " << prim.GetName() << std::endl;
    });
    return 0;
}
