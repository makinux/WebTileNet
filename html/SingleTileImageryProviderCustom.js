
    /**
     * Provides a single, top-level imagery tile.  The single image is assumed to use a
     * {@link GeographicTilingScheme}.
     *
     * @alias SingleTileImageryProviderCustom
     * @constructor
     *
     * @param {Object} options Object with the following properties:
     * @param {String} options.url The url for the tile.
     * @param {Rectangle} [options.rectangle=Rectangle.MAX_VALUE] The rectangle, in radians, covered by the image.
     * @param {Credit|String} [options.credit] A credit for the data source, which is displayed on the canvas.
     * @param {Ellipsoid} [options.ellipsoid] The ellipsoid.  If not specified, the WGS84 ellipsoid is used.
     * @param {Object} [options.proxy] A proxy to use for requests. This object is expected to have a getURL function which returns the proxied URL, if needed.
     *
     * @see ArcGisMapServerImageryProvider
     * @see BingMapsImageryProvider
     * @see GoogleEarthEnterpriseMapsProvider
     * @see createOpenStreetMapImageryProvider
     * @see createTileMapServiceImageryProvider
     * @see WebMapServiceImageryProvider
     * @see WebMapTileServiceImageryProvider
     * @see UrlTemplateImageryProvider
     */
    function SingleTileImageryProviderCustom(options) {
        options = Cesium.defaultValue(options, {});

        var canvas = options.canvas;

        //>>includeStart('debug', pragmas.debug);
        if (!Cesium.defined(canvas)) {
            throw new Cesium.DeveloperError('canvas is required.');
        }
        //>>includeEnd('debug');

        var rectangle = Cesium.defaultValue(options.rectangle, Cesium.Rectangle.MAX_VALUE);
        var tilingScheme = new Cesium.GeographicTilingScheme({
            rectangle : rectangle,
            numberOfLevelZeroTilesX : 1,
            numberOfLevelZeroTilesY : 1,
            ellipsoid : options.ellipsoid
        });
        this._tilingScheme = tilingScheme;

        this._image = undefined;
        this._texture = undefined;
        this._tileWidth = 0;
        this._tileHeight = 0;

        this._errorEvent = new Cesium.Event();

        this._ready = false;
        this._readyPromise = Cesium.when.defer();

        var credit = options.credit;
        if (typeof credit === 'string') {
            credit = new Cesium.Credit(credit);
        }
        this._credit = credit;

        var that = this;
        var error;

        function incanvas(canvas) {
            that._image = canvas;
            that._tileWidth = canvas.width;
            that._tileHeight = canvas.height;
            that._ready = true;
            that._readyPromise.resolve(true);
            Cesium.TileProviderError.handleSuccess(that._errorEvent);
        }

        incanvas(canvas);
    }

     Object.defineProperties(SingleTileImageryProviderCustom.prototype, {

        /**
         * Gets the width of each tile, in pixels. This function should
         * not be called before {@link SingleTileImageryProviderCustom#ready} returns true.
         * @memberof SingleTileImageryProviderCustom.prototype
         * @type {Number}
         * @readonly
         */
        tileWidth : {
            get : function() {
                //>>includeStart('debug', pragmas.debug);
                if (!this._ready) {
                    throw new Cesium.DeveloperError('tileWidth must not be called before the imagery provider is ready.');
                }
                //>>includeEnd('debug');

                return this._tileWidth;
            }
        },

        /**
         * Gets the height of each tile, in pixels.  This function should
         * not be called before {@link SingleTileImageryProviderCustom#ready} returns true.
         * @memberof SingleTileImageryProviderCustom.prototype
         * @type {Number}
         * @readonly
         */
        tileHeight: {
            get : function() {
                //>>includeStart('debug', pragmas.debug);
                if (!this._ready) {
                    throw new Cesium.DeveloperError('tileHeight must not be called before the imagery provider is ready.');
                }
                //>>includeEnd('debug');

                return this._tileHeight;
            }
        },

        /**
         * Gets the maximum level-of-detail that can be requested.  This function should
         * not be called before {@link SingleTileImageryProviderCustom#ready} returns true.
         * @memberof SingleTileImageryProviderCustom.prototype
         * @type {Number}
         * @readonly
         */
        maximumLevel : {
            get : function() {
                //>>includeStart('debug', pragmas.debug);
                if (!this._ready) {
                    throw new Cesium.DeveloperError('maximumLevel must not be called before the imagery provider is ready.');
                }
                //>>includeEnd('debug');

                return 0;
            }
        },

        /**
         * Gets the minimum level-of-detail that can be requested.  This function should
         * not be called before {@link SingleTileImageryProviderCustom#ready} returns true.
         * @memberof SingleTileImageryProviderCustom.prototype
         * @type {Number}
         * @readonly
         */
        minimumLevel : {
            get : function() {
                //>>includeStart('debug', pragmas.debug);
                if (!this._ready) {
                    throw new Cesium.DeveloperError('minimumLevel must not be called before the imagery provider is ready.');
                }
                //>>includeEnd('debug');

                return 0;
            }
        },

        /**
         * Gets the tiling scheme used by this provider.  This function should
         * not be called before {@link SingleTileImageryProviderCustom#ready} returns true.
         * @memberof SingleTileImageryProviderCustom.prototype
         * @type {TilingScheme}
         * @readonly
         */
        tilingScheme : {
            get : function() {
                //>>includeStart('debug', pragmas.debug);
                if (!this._ready) {
                    throw new Cesium.DeveloperError('tilingScheme must not be called before the imagery provider is ready.');
                }
                //>>includeEnd('debug');

                return this._tilingScheme;
            }
        },

        /**
         * Gets the rectangle, in radians, of the imagery provided by this instance.  This function should
         * not be called before {@link SingleTileImageryProviderCustom#ready} returns true.
         * @memberof SingleTileImageryProviderCustom.prototype
         * @type {Rectangle}
         * @readonly
         */
        rectangle : {
            get : function() {
                return this._tilingScheme.rectangle;
            }
        },

        /**
         * Gets the tile discard policy.  If not undefined, the discard policy is responsible
         * for filtering out "missing" tiles via its shouldDiscardImage function.  If this function
         * returns undefined, no tiles are filtered.  This function should
         * not be called before {@link SingleTileImageryProviderCustom#ready} returns true.
         * @memberof SingleTileImageryProviderCustom.prototype
         * @type {TileDiscardPolicy}
         * @readonly
         */
        tileDiscardPolicy : {
            get : function() {
                //>>includeStart('debug', pragmas.debug);
                if (!this._ready) {
                    throw new Cesium.DeveloperError('tileDiscardPolicy must not be called before the imagery provider is ready.');
                }
                //>>includeEnd('debug');

                return undefined;
            }
        },

        /**
         * Gets an event that is raised when the imagery provider encounters an asynchronous error.  By subscribing
         * to the event, you will be notified of the error and can potentially recover from it.  Event listeners
         * are passed an instance of {@link TileProviderError}.
         * @memberof SingleTileImageryProviderCustom.prototype
         * @type {Event}
         * @readonly
         */
        errorEvent : {
            get : function() {
                return this._errorEvent;
            }
        },

        /**
         * Gets a value indicating whether or not the provider is ready for use.
         * @memberof SingleTileImageryProviderCustom.prototype
         * @type {Boolean}
         * @readonly
         */
        ready : {
            get : function() {
                return this._ready;
            }
        },

        /**
         * Gets a promise that resolves to true when the provider is ready for use.
         * @memberof SingleTileImageryProviderCustom.prototype
         * @type {Promise.<Boolean>}
         * @readonly
         */
        readyPromise : {
            get : function() {
                return this._readyPromise.promise;
            }
        },

        /**
         * Gets the credit to display when this imagery provider is active.  Typically this is used to credit
         * the source of the imagery.  This function should not be called before {@link SingleTileImageryProviderCustom#ready} returns true.
         * @memberof SingleTileImageryProviderCustom.prototype
         * @type {Credit}
         * @readonly
         */
        credit : {
            get : function() {
                return this._credit;
            }
        },

        /**
         * Gets a value indicating whether or not the images provided by this imagery provider
         * include an alpha channel.  If this property is false, an alpha channel, if present, will
         * be ignored.  If this property is true, any images without an alpha channel will be treated
         * as if their alpha is 1.0 everywhere.  When this property is false, memory usage
         * and texture upload time are reduced.
         * @memberof SingleTileImageryProviderCustom.prototype
         * @type {Boolean}
         * @readonly
         */
        hasAlphaChannel : {
            get : function() {
                return true;
            }
        }
    });

    /**
     * Gets the credits to be displayed when a given tile is displayed.
     *
     * @param {Number} x The tile X coordinate.
     * @param {Number} y The tile Y coordinate.
     * @param {Number} level The tile level;
     * @returns {Credit[]} The credits to be displayed when the tile is displayed.
     *
     * @exception {DeveloperError} <code>getTileCredits</code> must not be called before the imagery provider is ready.
     */
    SingleTileImageryProviderCustom.prototype.getTileCredits = function(x, y, level) {
        return undefined;
    };

    /**
     * Requests the image for a given tile.  This function should
     * not be called before {@link SingleTileImageryProviderCustom#ready} returns true.
     *
     * @param {Number} x The tile X coordinate.
     * @param {Number} y The tile Y coordinate.
     * @param {Number} level The tile level.
     * @param {Request} [request] The request object. Intended for internal use only.
     * @returns {Promise.<Image|Canvas>|undefined} A promise for the image that will resolve when the image is available, or
     *          undefined if there are too many active requests to the server, and the request
     *          should be retried later.  The resolved image may be either an
     *          Image or a Canvas DOM object.
     *
     * @exception {DeveloperError} <code>requestImage</code> must not be called before the imagery provider is ready.
     */
    SingleTileImageryProviderCustom.prototype.requestImage = function(x, y, level, request) {
        //>>includeStart('debug', pragmas.debug);
        if (!this._ready) {
            throw new Cesium.DeveloperError('requestImage must not be called before the imagery provider is ready.');
        }
        //>>includeEnd('debug');

        return this._image;
    };

    /**
     * Picking features is not currently supported by this imagery provider, so this function simply returns
     * undefined.
     *
     * @param {Number} x The tile X coordinate.
     * @param {Number} y The tile Y coordinate.
     * @param {Number} level The tile level.
     * @param {Number} longitude The longitude at which to pick features.
     * @param {Number} latitude  The latitude at which to pick features.
     * @return {Promise.<ImageryLayerFeatureInfo[]>|undefined} A promise for the picked features that will resolve when the asynchronous
     *                   picking completes.  The resolved value is an array of {@link ImageryLayerFeatureInfo}
     *                   instances.  The array may be empty if no features are found at the given location.
     *                   It may also be undefined if picking is not supported.
     */
    SingleTileImageryProviderCustom.prototype.pickFeatures = function(x, y, level, longitude, latitude) {
        return undefined;
    };
