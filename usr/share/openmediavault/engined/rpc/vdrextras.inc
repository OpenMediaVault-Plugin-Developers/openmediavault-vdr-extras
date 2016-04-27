<?php

/**
 * Copyright (C) 2014 OpenMediaVault Plugin Developers.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

namespace OMV\Engined\Rpc;

use OMV\Config\Database;
use OMV\Engine\Notify\Dispatcher;
use OMV\Rpc\ServiceAbstract;

class VdrExtras extends ServiceAbstract
{
    /** @var Database */
    private $database;

    /** @var Dispatcher */
    private $dispatcher;

    /** @var string */
    private $eventMessagePath = 'org.openmediavault.conf.service.vdr';

    /** @var string */
    private $liveDataModelPath = 'conf.service.vdr.extras.live';

    /** @var string */
    private $streamdevDataModelPath = 'conf.service.vdr.extras.streamdev';

    /** @var string */
    private $vdradminamDataModelPath = 'conf.service.vdr.extras.vdradminam';

    /** @var string */
    private $vdradminamEventMessagePath = 'org.openmediavault.conf.service.vdr.extras.vdradminam';

    public function __construct(Database $database = null, Dispatcher $dispatcher = null)
    {
        $this->database = $database ? $database : Database::getInstance();
        $this->dispatcher = $dispatcher ? $dispatcher : Dispatcher::getInstance();
    }

    /**
     * Get the name of the RPC service.
     *
     * @return string
     */
    public function getName()
    {
        return 'VdrExtras';
    }

    /**
     * Initialize the RPC service.
     *
     * @return void
     */
    public function initialize()
    {
        $this->registerMethod('getLiveSettings');
        $this->registerMethod('setLiveSettings');
        $this->registerMethod('getStreamdevSettings');
        $this->registerMethod('setStreamdevSettings');
        $this->registerMethod('getVdradminamSettings');
        $this->registerMethod('setVdradminamSettings');
    }

    /**
     * Get the Live settings.
     *
     * @param array $params  The method paramaters.
     * @param array $context The context of the caller.
     *
     * @return array
     */
    public function getLiveSettings($params, $context)
    {
        $this->validateMethodContext($context, ['role' => OMV_ROLE_ADMINISTRATOR]);

        $object = $this->database->get($this->liveDataModelPath);

        return $object->getAssoc();
    }

    /**
     * Set the Live settings.
     *
     * @param array $params  The method paramaters.
     * @param array $context The context of the caller.
     *
     * @return array
     */
    public function setLiveSettings($params, $context)
    {
        $this->validateMethodContext($context, ['role' => OMV_ROLE_ADMINISTRATOR]);
        $this->validateMethodParams($params, 'rpc.vdr.extras.setlivesettings');

        $object = $this->database->get($this->liveDataModelPath);
        $object->setAssoc($params);

        $this->database->set($object);
        $this->dispatcher->notify(OMV_NOTIFY_MODIFY, $this->eventMessagePath);
    }

    /**
     * Get the Streamdev settings.
     *
     * @param array $params  The method paramaters.
     * @param array $context The context of the caller.
     *
     * @return array
     */
    public function getStreamdevSettings($params, $context)
    {
        $this->validateMethodContext($context, ['role' => OMV_ROLE_ADMINISTRATOR]);

        $object = $this->database->get($this->streamdevDataModelPath);

        return $object->getAssoc();
    }

    /**
     * Set the Streamdev settings.
     *
     * @param array $params  The method paramaters.
     * @param array $context The context of the caller.
     *
     * @return array
     */
    public function setStreamdevSettings($params, $context)
    {
        $this->validateMethodContext($context, ['role' => OMV_ROLE_ADMINISTRATOR]);
        $this->validateMethodParams($params, 'rpc.vdr.extras.setstreamdevsettings');

        $object = $this->database->get($this->streamdevDataModelPath);
        $object->setAssoc($params);

        $this->database->set($object);
        $this->dispatcher->notify(OMV_NOTIFY_MODIFY, $this->eventMessagePath);
    }

    /**
     * Get the VDRAdmin-AM settings.
     *
     * @param array $params  The method paramaters.
     * @param array $context The context of the caller.
     *
     * @return array
     */
    public function getVdradminamSettings($params, $context)
    {
        $this->validateMethodContext($context, ['role' => OMV_ROLE_ADMINISTRATOR]);

        $object = $this->database->get($this->vdradminamDataModelPath);

        return $object->getAssoc();
    }

    /**
     * Set VDRAdmin-AM settings.
     *
     * @param array $params  The method paramaters.
     * @param array $context The context of the caller.
     *
     * @return array
     */
    public function setVdradminamSettings($params, $context)
    {
        $this->validateMethodContext($context, ['role' => OMV_ROLE_ADMINISTRATOR]);
        $this->validateMethodParams($params, 'rpc.vdr.extras.setvdradminamsettings');

        $object = $this->database->get($this->vdradminamDataModelPath);
        $object->setAssoc($params);

        $this->database->set($object);
        $this->dispatcher->notify(OMV_NOTIFY_MODIFY, $this->eventMessagePath);
        $this->dispatcher->notify(OMV_NOTIFY_MODIFY, $this->vdradminamEventMessagePath);
    }
}
