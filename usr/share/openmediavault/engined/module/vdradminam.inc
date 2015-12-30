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
require_once "openmediavault/module.inc";
require_once "openmediavault/notify.inc";
require_once "openmediavault/systemctl.inc";

class OMVModuleVdradminam extends OMVModuleServiceAbstract implements
    OMVINotifyListener,
    OMVIModuleServiceStatus
{
    private function getEventMessagePath()
    {
        return "org.openmediavault.services.vdr.extras.vdradminam";
    }

    /**
     * Get the service configuration XPath.
     *
     * @return string
     */
    private function getXpath()
    {
        return "/config/services/vdrextras/vdradminam";
    }

    /**
     * Get the module name.
     *
     * @return string
     */
    public function getName()
    {
        return "vdradmin-am";
    }


    /**
     * Get the status of the service.
     *
     * @return array
     *
     * @throws OMVException
     */
    public function getStatus()
    {
        global $xmlConfig;

        $object = $xmlConfig->get($this->getXpath());

        if (is_null($object)) {
            throw new OMVException(
                OMVErrorMsg::E_CONFIG_GET_OBJECT_FAILED,
                $this->getXpath()
            );
        }

        $systemCtl = new OMVSystemCtl($this->getName());

        return [
            "name" => $this->getName(),
            "title" => gettext("VDRAdmin-AM"),
            "enabled" => boolval($object["enable"]),
            "running" => $systemCtl->isActive()
        ];
    }

    public function shouldStart()
    {
        return ["vdr"];
    }

    public function shouldStop()
    {
        return ["vdr"];
    }

    /**
     * Start the managed service.
     *
     * @return void
     *
     * @throws OMVException
     */
    public function startService()
    {
        global $xmlConfig;

        $object = $xmlConfig->get($this->getXpath());

        if (is_null($object)) {
            throw new OMVException(
                OMVErrorMsg::E_CONFIG_GET_OBJECT_FAILED,
                $this->getXpath()
            );
        }

        if (!boolval($object["enable"])) {
            return;
        }

        $systemCtl = new OMVSystemCtl($this->getName());
        $systemCtl->enable(true);
    }

    /**
     * Stop the managed service.
     *
     * @return void
     */
    public function stopService()
    {
        $systemCtl = new OMVSystemCtl($this->getName());
        $systemCtl->disable(true);
    }

    /**
     * Bind listeners.
     *
     * @param OMVNotifyDispatcher $dispatcher
     * @return void
     */
    public function bindListeners(OMVNotifyDispatcher $dispatcher)
    {
        $dispatcher->addListener(
            OMV_NOTIFY_MODIFY,
            $this->getEventMessagePath(),
            [$this, "setDirty"]
        );
    }
}

// Register the Module
$moduleMgr = &OMVModuleMgr::getInstance();
$moduleMgr->registerModule(new OMVModuleVdradminam());
