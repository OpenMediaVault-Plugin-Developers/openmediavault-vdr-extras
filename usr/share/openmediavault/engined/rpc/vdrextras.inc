<?php

/**
 * Copyright (C) 2014 OpenMediaVault Plugin Developers
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

require_once "openmediavault/config.inc";
require_once "openmediavault/error.inc";
require_once "openmediavault/notify.inc";
require_once "openmediavault/rpcservice.inc";

class OMVRpcServiceVdrExtras extends OMVRpcServiceAbstract
{
    private function getVdrEventMessagePath()
    {
        return "org.openmediavault.services.vdr";
    }

    private function getVdradminamEventMessagePath()
    {
        return "org.openmediavault.services.vdr.extras.vdradminam";
    }

    private function getXpath()
    {
        return "/config/services/vdrextras";
    }

    private function getLiveXpath()
    {
        return sprintf("%s/live", $this->getXpath());
    }

    private function getStreamdevXpath()
    {
        return sprintf("%s/streamdev", $this->getXpath());
    }

    private function getVdradminamXpath()
    {
        return sprintf("%s/vdradminam", $this->getXpath());
    }

    public function getName()
    {
        return "VdrExtras";
    }

    public function initialize()
    {
        $this->registerMethod("getLiveSettings");
        $this->registerMethod("setLiveSettings");
        $this->registerMethod("getStreamdevSettings");
        $this->registerMethod("setStreamdevSettings");
        $this->registerMethod("getVdradminamSettings");
        $this->registerMethod("setVdradminamSettings");
    }

    public function getLiveSettings($params, $context)
    {
        global $xmlConfig;

        // Validate the RPC caller context.
        $this->validateMethodContext($context, [
            "role" => OMV_ROLE_ADMINISTRATOR
        ]);

        // Get the configuration object
        $object = $this->load($this->getLiveXpath());

        $object["enable"] = boolval($object["enable"]);
        $object["port"] = intval($object["port"]);

        return $object;
    }

    public function setLiveSettings($params, $context)
    {
        global $xmlConfig;

        // Validate the RPC caller context.
        $this->validateMethodContext($context, [
            "role" => OMV_ROLE_ADMINISTRATOR
        ]);

        // Validate the parameters of the RPC service method.
        $this->validateMethodParams(
            $params,
            '{
                "type": "object",
                "properties": {
                    "enable": { "type": "boolean" },
                    "port": { "type": "integer", "minimum": 1024, "maximum": 65535 }
                }
            }'
        );

        $object = [
            "enable" => boolval($params["enable"]),
            "port" => intval($params["port"]),
        ];

        $this->save($object, $this->getLiveXpath());

        return $object;
    }

    public function getStreamdevSettings($params, $context)
    {
        global $xmlConfig;

        // Validate the RPC caller context.
        $this->validateMethodContext($context, [
            "role" => OMV_ROLE_ADMINISTRATOR
        ]);

        // Get the configuration object
        $object = $this->load($this->getStreamdevXpath());

        $object["enable"] = boolval($object["enable"]);
        $object["port"] = intval($object["port"]);

        return $object;
    }

    public function setStreamdevSettings($params, $context)
    {
        global $xmlConfig;

        // Validate the RPC caller context.
        $this->validateMethodContext($context, [
            "role" => OMV_ROLE_ADMINISTRATOR
        ]);

        // Validate the parameters of the RPC service method.
        $this->validateMethodParams(
            $params,
            '{
                "type": "object",
                "properties": {
                    "enable": { "type": "boolean" },
                    "port": { "type": "integer", "minimum": 1024, "maximum": 65535 },
                    "allowed_hosts": { "type": "string" }
                }
            }'
        );

        $object = [
            "enable" => boolval($params["enable"]),
            "port" => intval($params["port"]),
            "allowed_hosts" => $params["allowed_hosts"],
        ];

        $this->save($object, $this->getStreamdevXpath());

        return $object;
    }

    public function getVdradminamSettings($params, $context)
    {
        global $xmlConfig;

        // Validate the RPC caller context.
        $this->validateMethodContext($context, [
            "role" => OMV_ROLE_ADMINISTRATOR
        ]);

        // Get the configuration object
        $object = $this->load($this->getVdradminamXpath());

        $object["enable"] = boolval($object["enable"]);
        $object["port"] = intval($object["port"]);

        return $object;
    }

    public function setVdradminamSettings($params, $context)
    {
        global $xmlConfig;

        // Validate the RPC caller context.
        $this->validateMethodContext($context, [
            "role" => OMV_ROLE_ADMINISTRATOR
        ]);

        // Validate the parameters of the RPC service method.
        $this->validateMethodParams(
            $params,
            '{
                "type": "object",
                "properties": {
                    "enable": { "type": "boolean" },
                    "port": { "type": "integer", "minimum": 1024, "maximum": 65535 }
                }
            }'
        );

        $object = [
            "enable" => boolval($params["enable"]),
            "port" => intval($params["port"]),
        ];

        $this->save($object, $this->getVdradminamXpath());
        $this->notify($this->getVdradminamEventMessagePath());

        return $object;
    }

    private function load($xpath)
    {
        global $xmlConfig;

        $object = $xmlConfig->get($xpath);

        if (is_null($object)) {
            throw new OMVException(
                OMVErrorMsg::E_CONFIG_GET_OBJECT_FAILED,
                $xpath
            );
        }

        return $object;
    }

    private function save($object, $xpath)
    {
        global $xmlConfig;

        if ($xmlConfig->replace($xpath, $object) === false) {
            throw new OMVException(OMVErrorMsg::E_CONFIG_SET_OBJECT_FAILED);
        }

        $this->notify($this->getVdrEventMessagePath());

        return $object;
    }

    private function notify($eventPath, $object = null)
    {
        $dispatcher = &OMVNotifyDispatcher::getInstance();
        $dispatcher->notify(
            OMV_NOTIFY_MODIFY,
            $eventPath,
            $object
        );
    }
}

// Register the RPC service.
$rpcServiceMgr = &OMVRpcServiceMgr::getInstance();
$rpcServiceMgr->registerService(new OMVRpcServiceVdrExtras());
