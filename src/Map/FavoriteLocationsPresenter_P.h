#ifndef _OSMAND_CORE_FAVORITE_LOCATIONS_PRESENTER_P_H_
#define _OSMAND_CORE_FAVORITE_LOCATIONS_PRESENTER_P_H_

#include "stdlib_common.h"

#include "QtExtensions.h"
#include <QList>
#include <QSet>
#include <QHash>
#include <QReadWriteLock>

#include "OsmAndCore.h"
#include "PrivateImplementation.h"
#include "CommonTypes.h"
#include "IMapKeyedSymbolsProvider.h"
#include "MapMarkersCollection.h"

namespace OsmAnd
{
    class IFavoriteLocation;
    class IFavoriteLocationsCollection;

    class FavoriteLocationsPresenter;
    class FavoriteLocationsPresenter_P Q_DECL_FINAL
    {
        Q_DISABLE_COPY(FavoriteLocationsPresenter_P);

    private:
    protected:
        FavoriteLocationsPresenter_P(FavoriteLocationsPresenter* const owner);

        mutable QReadWriteLock _visibilitySettingsLock;
        QSet<QString> _hiddenGroups;
        QSet< std::shared_ptr<const IFavoriteLocation> > _hiddenFavoriteLocations;

        const std::shared_ptr<MapMarkersCollection> _markersCollection;

        mutable QReadWriteLock _favoriteLocationToMarkerMapLock;
        QHash< std::shared_ptr<const IFavoriteLocation>, std::shared_ptr<MapMarker> > _favoriteLocationToMarkerMap;

        void subscribeToChanges();
        void unsubscribeToChanges();
        void syncFavoriteLocationMarkers();
    public:
        ~FavoriteLocationsPresenter_P();

        ImplementationInterface<FavoriteLocationsPresenter> owner;

        bool isGroupVisible(const QString& group) const;
        void setIsGroupVisible(const QString& group, const bool isVisible);
        void showGroup(const QString& group);
        void hideGroup(const QString& group);

        bool isFavoriteLocationVisible(const std::shared_ptr<const IFavoriteLocation>& favoriteLocation, const bool checkGroup) const;
        void setIsFavoriteLocationVisible(const std::shared_ptr<const IFavoriteLocation>& favoriteLocation, const bool isVisible);
        void showFavoriteLocation(const std::shared_ptr<const IFavoriteLocation>& favoriteLocation);
        void hideFavoriteLocation(const std::shared_ptr<const IFavoriteLocation>& favoriteLocation);

        QList<IMapKeyedSymbolsProvider::Key> getProvidedDataKeys() const;
        bool obtainData(
            const IMapKeyedSymbolsProvider::Key key,
            std::shared_ptr<MapKeyedData>& outKeyedData,
            const IQueryController* const queryController);

    friend class OsmAnd::FavoriteLocationsPresenter;
    };
}

#endif // !defined(_OSMAND_CORE_FAVORITE_LOCATIONS_PRESENTER_P_H_)
