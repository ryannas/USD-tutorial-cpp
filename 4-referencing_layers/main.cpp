#include <iostream>

#include <pxr/usd/usd/stage.h>
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

    // create a ref stage
    auto ref_stage = pxr::UsdStage::CreateNew("refexample.usda");

    // add ref to helloworld
    auto ref_sphere = ref_stage->OverridePrim(pxr::SdfPath("/refSphere"));
    ref_sphere.GetReferences().AddReference(pxr::SdfReference("helloworld.usda"));

    // discard ref's transformation
    auto ref_xform = pxr::UsdGeomXformable(ref_sphere);
    ref_xform.SetXformOpOrder({});

    // add another ref to helloworld
    auto ref_sphere_2 = ref_stage->OverridePrim(pxr::SdfPath("/refSphere2"));
    ref_sphere_2.GetReferences().AddReference(pxr::SdfReference("helloworld.usda"));

    // save stage
    ref_stage->GetRootLayer()->Save();

    std::cout << "\nref usd:" << std::endl;
    ref_stage->GetRootLayer()->ExportToString(&result);
    std::cout << result << std::endl;

    return 0;
}
