/*-
 * This file is provided under a dual BSD/GPLv2 license.  When using or 
 *   redistributing this file, you may do so under either license.
 * 
 *   GPL LICENSE SUMMARY
 * 
 *   Copyright(c) 2010-2012 Intel Corporation. All rights reserved.
 * 
 *   This program is free software; you can redistribute it and/or modify 
 *   it under the terms of version 2 of the GNU General Public License as
 *   published by the Free Software Foundation.
 * 
 *   This program is distributed in the hope that it will be useful, but 
 *   WITHOUT ANY WARRANTY; without even the implied warranty of 
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU 
 *   General Public License for more details.
 * 
 *   You should have received a copy of the GNU General Public License 
 *   along with this program; if not, write to the Free Software 
 *   Foundation, Inc., 51 Franklin St - Fifth Floor, Boston, MA 02110-1301 USA.
 *   The full GNU General Public License is included in this distribution 
 *   in the file called LICENSE.GPL.
 * 
 *   Contact Information:
 *   Intel Corporation
 * 
 *   BSD LICENSE 
 * 
 *   Copyright(c) 2010-2012 Intel Corporation. All rights reserved.
 *   All rights reserved.
 * 
 *   Redistribution and use in source and binary forms, with or without 
 *   modification, are permitted provided that the following conditions 
 *   are met:
 * 
 *     * Redistributions of source code must retain the above copyright 
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright 
 *       notice, this list of conditions and the following disclaimer in 
 *       the documentation and/or other materials provided with the 
 *       distribution.
 *     * Neither the name of Intel Corporation nor the names of its 
 *       contributors may be used to endorse or promote products derived 
 *       from this software without specific prior written permission.
 * 
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
 *   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
 *   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR 
 *   A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
 *   OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
 *   SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
 *   LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, 
 *   DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY 
 *   THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
 *   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
 *   OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 * 
 */

/**
 * @file
 *
 * This file contains a list of the PCI device IDs recognised by DPDK, which
 * can be used to fill out an array of structures describing the devices.
 *
 * Currently two families of devices are recognised: those supported by the
 * IGB driver, and those supported by the IXGBE driver. The inclusion of these
 * in an array built using this file depends on the definition of
 * RTE_LIBRTE_IGB_PMD and RTE_LIBRTE_IXGBE_PMD at the time when this file is
 * included.
 *
 * In order to populate an array, the user of this file must define this macro:
 * RTE_PCI_DEV_ID_DECL(vendorID, deviceID). For example:
 *
 * @code
 * struct device {
 *     int vend;
 *     int dev;
 * };
 *
 * struct device devices[] = {
 * #define RTE_PCI_DEV_ID_DECL(vendorID, deviceID) {vend, dev},
 * #include <rte_pci_dev_ids.h>
 * };
 * @endcode
 *
 * Note that this file can be included multiple times within the same file.
 */

#ifndef RTE_PCI_DEV_ID_DECL
#error "You must define RTE_PCI_DEV_ID_DECL before including rte_pci_dev_ids.h"
#endif

#ifndef PCI_VENDOR_ID_INTEL
/** Vendor ID used by Intel devices */
#define PCI_VENDOR_ID_INTEL 0x8086
#endif

/******************** Physical IGB devices from e1000_hw.h ********************/
#ifdef RTE_LIBRTE_IGB_PMD

#define E1000_DEV_ID_82576                      0x10C9
#define E1000_DEV_ID_82576_FIBER                0x10E6
#define E1000_DEV_ID_82576_SERDES               0x10E7
#define E1000_DEV_ID_82576_QUAD_COPPER          0x10E8
#define E1000_DEV_ID_82576_QUAD_COPPER_ET2      0x1526
#define E1000_DEV_ID_82576_NS                   0x150A
#define E1000_DEV_ID_82576_NS_SERDES            0x1518
#define E1000_DEV_ID_82576_SERDES_QUAD          0x150D
#define E1000_DEV_ID_82575EB_COPPER             0x10A7
#define E1000_DEV_ID_82575EB_FIBER_SERDES       0x10A9
#define E1000_DEV_ID_82575GB_QUAD_COPPER        0x10D6
#define E1000_DEV_ID_82580_COPPER               0x150E
#define E1000_DEV_ID_82580_FIBER                0x150F
#define E1000_DEV_ID_82580_SERDES               0x1510
#define E1000_DEV_ID_82580_SGMII                0x1511
#define E1000_DEV_ID_82580_COPPER_DUAL          0x1516
#define E1000_DEV_ID_82580_QUAD_FIBER           0x1527
#define E1000_DEV_ID_I350_COPPER                0x1521
#define E1000_DEV_ID_I350_FIBER                 0x1522
#define E1000_DEV_ID_I350_SERDES                0x1523
#define E1000_DEV_ID_I350_SGMII                 0x1524
#define E1000_DEV_ID_I350_DA4                   0x1546
#define E1000_DEV_ID_DH89XXCC_SGMII             0x0438
#define E1000_DEV_ID_DH89XXCC_SERDES            0x043A
#define E1000_DEV_ID_DH89XXCC_BACKPLANE         0x043C
#define E1000_DEV_ID_DH89XXCC_SFP               0x0440

RTE_PCI_DEV_ID_DECL(PCI_VENDOR_ID_INTEL, E1000_DEV_ID_82576)
RTE_PCI_DEV_ID_DECL(PCI_VENDOR_ID_INTEL, E1000_DEV_ID_82576_FIBER)
RTE_PCI_DEV_ID_DECL(PCI_VENDOR_ID_INTEL, E1000_DEV_ID_82576_SERDES)
RTE_PCI_DEV_ID_DECL(PCI_VENDOR_ID_INTEL, E1000_DEV_ID_82576_QUAD_COPPER)
RTE_PCI_DEV_ID_DECL(PCI_VENDOR_ID_INTEL, E1000_DEV_ID_82576_QUAD_COPPER_ET2)
RTE_PCI_DEV_ID_DECL(PCI_VENDOR_ID_INTEL, E1000_DEV_ID_82576_NS)
RTE_PCI_DEV_ID_DECL(PCI_VENDOR_ID_INTEL, E1000_DEV_ID_82576_NS_SERDES)
RTE_PCI_DEV_ID_DECL(PCI_VENDOR_ID_INTEL, E1000_DEV_ID_82576_SERDES_QUAD)

/* This device is the on-board NIC on some development boards. */
#ifdef RTE_PCI_DEV_USE_82575EB_COPPER
RTE_PCI_DEV_ID_DECL(PCI_VENDOR_ID_INTEL, E1000_DEV_ID_82575EB_COPPER)
#endif

RTE_PCI_DEV_ID_DECL(PCI_VENDOR_ID_INTEL, E1000_DEV_ID_82575EB_FIBER_SERDES)
RTE_PCI_DEV_ID_DECL(PCI_VENDOR_ID_INTEL, E1000_DEV_ID_82575GB_QUAD_COPPER)

RTE_PCI_DEV_ID_DECL(PCI_VENDOR_ID_INTEL, E1000_DEV_ID_82580_COPPER)
RTE_PCI_DEV_ID_DECL(PCI_VENDOR_ID_INTEL, E1000_DEV_ID_82580_FIBER)
RTE_PCI_DEV_ID_DECL(PCI_VENDOR_ID_INTEL, E1000_DEV_ID_82580_SERDES)
RTE_PCI_DEV_ID_DECL(PCI_VENDOR_ID_INTEL, E1000_DEV_ID_82580_SGMII)
RTE_PCI_DEV_ID_DECL(PCI_VENDOR_ID_INTEL, E1000_DEV_ID_82580_COPPER_DUAL)
RTE_PCI_DEV_ID_DECL(PCI_VENDOR_ID_INTEL, E1000_DEV_ID_82580_QUAD_FIBER)

/* This device is the on-board NIC on some development boards. */
#ifndef RTE_PCI_DEV_NO_USE_I350_COPPER
RTE_PCI_DEV_ID_DECL(PCI_VENDOR_ID_INTEL, E1000_DEV_ID_I350_COPPER)
#endif

RTE_PCI_DEV_ID_DECL(PCI_VENDOR_ID_INTEL, E1000_DEV_ID_I350_FIBER)
RTE_PCI_DEV_ID_DECL(PCI_VENDOR_ID_INTEL, E1000_DEV_ID_I350_SERDES)
RTE_PCI_DEV_ID_DECL(PCI_VENDOR_ID_INTEL, E1000_DEV_ID_I350_SGMII)
RTE_PCI_DEV_ID_DECL(PCI_VENDOR_ID_INTEL, E1000_DEV_ID_I350_DA4)
RTE_PCI_DEV_ID_DECL(PCI_VENDOR_ID_INTEL, E1000_DEV_ID_DH89XXCC_SGMII)
RTE_PCI_DEV_ID_DECL(PCI_VENDOR_ID_INTEL, E1000_DEV_ID_DH89XXCC_SERDES)
RTE_PCI_DEV_ID_DECL(PCI_VENDOR_ID_INTEL, E1000_DEV_ID_DH89XXCC_BACKPLANE)
RTE_PCI_DEV_ID_DECL(PCI_VENDOR_ID_INTEL, E1000_DEV_ID_DH89XXCC_SFP)

#endif /* RTE_LIBRTE_IGB_PMD */


/****************** Physical IXGBE devices from ixgbe_type.h ******************/
#ifdef RTE_LIBRTE_IXGBE_PMD

#define IXGBE_DEV_ID_82598                      0x10B6
#define IXGBE_DEV_ID_82598_BX                   0x1508
#define IXGBE_DEV_ID_82598AF_DUAL_PORT          0x10C6
#define IXGBE_DEV_ID_82598AF_SINGLE_PORT        0x10C7
#define IXGBE_DEV_ID_82598AT                    0x10C8
#define IXGBE_DEV_ID_82598AT2                   0x150B
#define IXGBE_DEV_ID_82598EB_SFP_LOM            0x10DB
#define IXGBE_DEV_ID_82598EB_CX4                0x10DD
#define IXGBE_DEV_ID_82598_CX4_DUAL_PORT        0x10EC
#define IXGBE_DEV_ID_82598_DA_DUAL_PORT         0x10F1
#define IXGBE_DEV_ID_82598_SR_DUAL_PORT_EM      0x10E1
#define IXGBE_DEV_ID_82598EB_XF_LR              0x10F4
#define IXGBE_DEV_ID_82599_KX4                  0x10F7
#define IXGBE_DEV_ID_82599_KX4_MEZZ             0x1514
#define IXGBE_DEV_ID_82599_KR                   0x1517
#define IXGBE_DEV_ID_82599_COMBO_BACKPLANE      0x10F8
#define IXGBE_SUBDEV_ID_82599_KX4_KR_MEZZ       0x000C
#define IXGBE_DEV_ID_82599_CX4                  0x10F9
#define IXGBE_DEV_ID_82599_SFP                  0x10FB
#define IXGBE_SUBDEV_ID_82599_SFP               0x11A9
#define IXGBE_DEV_ID_82599_BACKPLANE_FCOE       0x152A
#define IXGBE_DEV_ID_82599_SFP_FCOE             0x1529
#define IXGBE_DEV_ID_82599_SFP_EM               0x1507
#define IXGBE_DEV_ID_82599EN_SFP                0x1557
#define IXGBE_DEV_ID_82599_XAUI_LOM             0x10FC
#define IXGBE_DEV_ID_82599_T3_LOM               0x151C
#define IXGBE_DEV_ID_X540T                      0x1528

RTE_PCI_DEV_ID_DECL(PCI_VENDOR_ID_INTEL, IXGBE_DEV_ID_82598)
RTE_PCI_DEV_ID_DECL(PCI_VENDOR_ID_INTEL, IXGBE_DEV_ID_82598_BX)
RTE_PCI_DEV_ID_DECL(PCI_VENDOR_ID_INTEL, IXGBE_DEV_ID_82598AF_DUAL_PORT)
RTE_PCI_DEV_ID_DECL(PCI_VENDOR_ID_INTEL, IXGBE_DEV_ID_82598AF_SINGLE_PORT)
RTE_PCI_DEV_ID_DECL(PCI_VENDOR_ID_INTEL, IXGBE_DEV_ID_82598AT)
RTE_PCI_DEV_ID_DECL(PCI_VENDOR_ID_INTEL, IXGBE_DEV_ID_82598AT2)
RTE_PCI_DEV_ID_DECL(PCI_VENDOR_ID_INTEL, IXGBE_DEV_ID_82598EB_SFP_LOM)
RTE_PCI_DEV_ID_DECL(PCI_VENDOR_ID_INTEL, IXGBE_DEV_ID_82598EB_CX4)
RTE_PCI_DEV_ID_DECL(PCI_VENDOR_ID_INTEL, IXGBE_DEV_ID_82598_CX4_DUAL_PORT)
RTE_PCI_DEV_ID_DECL(PCI_VENDOR_ID_INTEL, IXGBE_DEV_ID_82598_DA_DUAL_PORT)
RTE_PCI_DEV_ID_DECL(PCI_VENDOR_ID_INTEL, IXGBE_DEV_ID_82598_SR_DUAL_PORT_EM)
RTE_PCI_DEV_ID_DECL(PCI_VENDOR_ID_INTEL, IXGBE_DEV_ID_82598EB_XF_LR)
RTE_PCI_DEV_ID_DECL(PCI_VENDOR_ID_INTEL, IXGBE_DEV_ID_82599_KX4)
RTE_PCI_DEV_ID_DECL(PCI_VENDOR_ID_INTEL, IXGBE_DEV_ID_82599_KX4_MEZZ)
RTE_PCI_DEV_ID_DECL(PCI_VENDOR_ID_INTEL, IXGBE_DEV_ID_82599_KR)
RTE_PCI_DEV_ID_DECL(PCI_VENDOR_ID_INTEL, IXGBE_DEV_ID_82599_COMBO_BACKPLANE)
RTE_PCI_DEV_ID_DECL(PCI_VENDOR_ID_INTEL, IXGBE_SUBDEV_ID_82599_KX4_KR_MEZZ)
RTE_PCI_DEV_ID_DECL(PCI_VENDOR_ID_INTEL, IXGBE_DEV_ID_82599_CX4)
RTE_PCI_DEV_ID_DECL(PCI_VENDOR_ID_INTEL, IXGBE_DEV_ID_82599_SFP)
RTE_PCI_DEV_ID_DECL(PCI_VENDOR_ID_INTEL, IXGBE_SUBDEV_ID_82599_SFP)
RTE_PCI_DEV_ID_DECL(PCI_VENDOR_ID_INTEL, IXGBE_DEV_ID_82599_BACKPLANE_FCOE)
RTE_PCI_DEV_ID_DECL(PCI_VENDOR_ID_INTEL, IXGBE_DEV_ID_82599_SFP_FCOE)
RTE_PCI_DEV_ID_DECL(PCI_VENDOR_ID_INTEL, IXGBE_DEV_ID_82599_SFP_EM)
RTE_PCI_DEV_ID_DECL(PCI_VENDOR_ID_INTEL, IXGBE_DEV_ID_82599EN_SFP)
RTE_PCI_DEV_ID_DECL(PCI_VENDOR_ID_INTEL, IXGBE_DEV_ID_82599_XAUI_LOM)
RTE_PCI_DEV_ID_DECL(PCI_VENDOR_ID_INTEL, IXGBE_DEV_ID_82599_T3_LOM)
RTE_PCI_DEV_ID_DECL(PCI_VENDOR_ID_INTEL, IXGBE_DEV_ID_X540T)

#endif /* RTE_LIBRTE_IXGBE_PMD */
