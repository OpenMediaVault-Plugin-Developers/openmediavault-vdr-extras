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
// require("js/omv/workspace/form/Panel.js")

Ext.define("OMV.module.admin.service.vdr.extras.Base", {
    extend: "OMV.workspace.form.Panel",

    rpcService: "VdrExtras",

    webInterfaceEncrypted: false,

    getButtonItems: function() {
        var items = this.callParent(arguments);

        items.push({
            id: this.getId() + "-show",
            xtype: "button",
            text: _("Show"),
            icon: "images/search.png",
            iconCls: Ext.baseCSSPrefix + "btn-icon-16x16",
            scope: this,
            handler: function() {
                var protocol = this.webInterfaceEncrypted ? "https" : "http";
                var hostname = location.hostname;
                var port = this.getWebInterfacePort();

                var link = Ext.String.format("{0}://{1}:{2}", protocol, hostname, port);

                window.open(link, "_blank");
            }
        });

        return items;
    },

    getWebInterfacePort: function() {
        return this.getForm().findField("port").getValue();
    }
});
