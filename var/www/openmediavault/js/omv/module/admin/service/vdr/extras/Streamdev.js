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
// require("js/omv/module/admin/service/vdr/extras/Base.js")

Ext.define('OMV.module.admin.service.vdr.extras.Streamdev', {
    extend: 'OMV.module.admin.service.vdr.extras.Base',

    rpcGetMethod: 'getStreamdevSettings',
    rpcSetMethod: 'setStreamdevSettings',

    getFormItems: function() {
        return [{
            xtype: 'fieldset',
            title: _('General settings'),
            fieldDefaults: {
                labelSeparator: ''
            },
            items: [{
                xtype: 'checkbox',
                name: 'enable',
                fieldLabel: _('Enable'),
                checked: false
            }, {
                xtype: 'numberfield',
                name: 'port',
                fieldLabel: _('Port'),
                vtype: 'port',
                minValue: 1024,
                maxValue: 65535,
                allowDecimals: false,
                allowNegative: false,
                allowBlank: false,
                value: 3000
            }, {
                xtype: 'textfield',
                name: 'allowed_hosts',
                fieldLabel: _('Allowed hosts'),
                allowBlank: false
            }]
        }];
    }
});
