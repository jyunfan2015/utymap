#ifndef BUILDERS_TILEBUILDER_HPP_DEFINED
#define BUILDERS_TILEBUILDER_HPP_DEFINED

#include "QuadKey.hpp"
#include "builders/BuilderContext.hpp"
#include "builders/ElementBuilder.hpp"
#include "entities/Element.hpp"
#include "heightmap/ElevationProvider.hpp"
#include "index/GeoStore.hpp"
#include "mapcss/StyleProvider.hpp"
#include "meshing/MeshTypes.hpp"

#include <functional>
#include <string>
#include <memory>

namespace utymap { namespace builders {

// Responsible for building single tile.
class TileBuilder
{
public:

    typedef std::function<void(const utymap::meshing::Mesh&)> MeshCallback;
    typedef std::function<void(const utymap::entities::Element&)> ElementCallback;
    // Factory of element builders
    typedef std::function<std::shared_ptr<utymap::builders::ElementBuilder>(
        const utymap::builders::BuilderContext&)> ElementBuilderFactory;

    TileBuilder(utymap::index::GeoStore& geoStore,
                utymap::index::StringTable& stringTable,
                utymap::heightmap::ElevationProvider& eleProvider);

    ~TileBuilder();

    // Registers factory method for element builder.
    void registerElementBuilder(const std::string& name, ElementBuilderFactory factory);

    // Builds tile for given quadkey.
    void build(const utymap::QuadKey& quadKey,
               const utymap::mapcss::StyleProvider& styleProvider,
               MeshCallback meshFunc,
               ElementCallback elementFunc);

private:
    class TileBuilderImpl;
    std::unique_ptr<TileBuilderImpl> pimpl_;
};

}}
#endif // BUILDERS_TILEBUILDER_HPP_DEFINED
