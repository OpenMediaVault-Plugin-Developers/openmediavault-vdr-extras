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

// require("js/omv/WorkspaceManager.js")
// require("js/omv/workspace/tab/Panel.js")
// require("js/omv/module/admin/service/vdr/extras/Live.js")
// require("js/omv/module/admin/service/vdr/extras/Streamdev.js")
// require("js/omv/module/admin/service/vdr/extras/Vdradminam.js")

Ext.define("OMV.module.admin.service.vdr.Extras", {
    extend: "OMV.workspace.tab.Panel",
    requires: [
        "OMV.module.admin.service.vdr.extras.Live",
        "OMV.module.admin.service.vdr.extras.Streamdev",
        "OMV.module.admin.service.vdr.extras.Vdradminam"
    ],
    initComponent: function() {
        Ext.apply(this, {
            items: [
                Ext.create("OMV.module.admin.service.vdr.extras.Live", {
                    title: _("LIVE")
                }),
                Ext.create("OMV.module.admin.service.vdr.extras.Streamdev", {
                    title: _("Streamdev")
                }),
                Ext.create("OMV.module.admin.service.vdr.extras.Vdradminam", {
                    title: _("VDRAdmin-AM")
                })
            ]
        });

        this.callParent(arguments);
    }
});

OMV.WorkspaceManager.registerPanel({
    id: "extras",
    path: "/service/vdr",
    text: _("Extras"),
    position: 100,
    className: "OMV.module.admin.service.vdr.Extras"
});
