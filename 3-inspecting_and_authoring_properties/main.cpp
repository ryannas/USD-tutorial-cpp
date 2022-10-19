#include <iostream>

#include <pxr/usd/usd/stage.h>
#include <pxr/usd/usdGeom/xform.h>
#include <pxr/usd/usdGeom/sphere.h>
#include <pxr/usd/sdf/layer.h>

int main() {
    // create a new stage
    auto stage = pxr::UsdStage::CreateNew("helloworld.usda");
    auto xform = stage->DefinePrim(pxr::SdfPath("/hello"), pxr::TfToken("Xform"));
    auto sphere = stage->DefinePrim(pxr::SdfPath("/hello/world"), pxr::TfToken("Sphere"));

    // inspect prim's property names
    auto xform_property_names = xform.GetPropertyNames();
    auto sphere_property_names = sphere.GetPropertyNames();
    std::cout << "property names of xform:" << std::endl;
    for (const auto& pn : xform_property_names) {
        std::cout << "--" << pn << std::endl;
    }
    std::cout << "property names of sphere:" << std::endl;
    for (const auto& pn : sphere_property_names) {
        std::cout << "--" << pn << std::endl;
    }

    // modify sphere's radius and extent
    auto radius_attr = sphere.GetAttribute(pxr::TfToken("radius"));
    auto extent_attr = sphere.GetAttribute(pxr::TfToken("extent"));
    radius_attr.Set(3.0);

    pxr::VtValue extent_vtvalue = pxr::VtValue();
    if (extent_attr.Get(&extent_vtvalue)) {
        auto extent_value = extent_vtvalue.Get<pxr::VtArray<pxr::GfVec3f>>();
        for (auto &v: extent_value)
            v *= 3;
        extent_attr.Set(extent_value);
    }

    // modify sphere color with directly get attribute
    auto color = sphere.GetAttribute(pxr::TfToken("primvars:displayColor"));
    pxr::VtArray<pxr::GfVec3f> blue({{0, 0, 1}});
    color.Set(blue);

    // modify sphere color with usdgeom schema
    color = pxr::UsdGeomSphere(sphere).GetDisplayColorAttr();
    pxr::VtArray<pxr::GfVec3f> red({{1, 0, 0}});
    color.Set(red);

    // save changes
    stage->GetRootLayer()->Save();

    // output result
    std::cout << "\nresult:" << std::endl;
    std::string result;
    stage->GetRootLayer()->ExportToString(&result);
    std::cout << result << std::endl;

    return 0;
}
