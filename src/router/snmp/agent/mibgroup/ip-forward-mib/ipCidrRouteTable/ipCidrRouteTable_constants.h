/*
 * Note: this file originally auto-generated by mib2c using
 *  : generic-table-constants.m2c,v 1.5 2005/07/15 22:41:16 rstory Exp $
 *
 * $Id: ipCidrRouteTable_constants.h,v 1.4 2005/11/30 22:32:31 rstory Exp $
 */
#ifndef IPCIDRROUTETABLE_CONSTANTS_H
#define IPCIDRROUTETABLE_CONSTANTS_H

#ifdef __cplusplus
extern          "C" {
#endif


    /*
     * column number definitions for table ipCidrRouteTable 
     */
#define IPCIDRROUTETABLE_OID              1,3,6,1,2,1,4,24,4

#define COLUMN_IPCIDRROUTEDEST         1

#define COLUMN_IPCIDRROUTEMASK         2

#define COLUMN_IPCIDRROUTETOS         3

#define COLUMN_IPCIDRROUTENEXTHOP         4

#define COLUMN_IPCIDRROUTEIFINDEX         5
#define COLUMN_IPCIDRROUTEIFINDEX_FLAG    (0x1 << 4)

#define COLUMN_IPCIDRROUTETYPE         6
#define COLUMN_IPCIDRROUTETYPE_FLAG    (0x1 << 5)

#define COLUMN_IPCIDRROUTEPROTO         7

#define COLUMN_IPCIDRROUTEAGE         8

#define COLUMN_IPCIDRROUTEINFO         9
#define COLUMN_IPCIDRROUTEINFO_FLAG    (0x1 << 8)

#define COLUMN_IPCIDRROUTENEXTHOPAS         10
#define COLUMN_IPCIDRROUTENEXTHOPAS_FLAG    (0x1 << 9)

#define COLUMN_IPCIDRROUTEMETRIC1         11
#define COLUMN_IPCIDRROUTEMETRIC1_FLAG    (0x1 << 10)

#define COLUMN_IPCIDRROUTEMETRIC2         12
#define COLUMN_IPCIDRROUTEMETRIC2_FLAG    (0x1 << 11)

#define COLUMN_IPCIDRROUTEMETRIC3         13
#define COLUMN_IPCIDRROUTEMETRIC3_FLAG    (0x1 << 12)

#define COLUMN_IPCIDRROUTEMETRIC4         14
#define COLUMN_IPCIDRROUTEMETRIC4_FLAG    (0x1 << 13)

#define COLUMN_IPCIDRROUTEMETRIC5         15
#define COLUMN_IPCIDRROUTEMETRIC5_FLAG    (0x1 << 14)

#define COLUMN_IPCIDRROUTESTATUS         16
#define COLUMN_IPCIDRROUTESTATUS_FLAG    (0x1 << 15)


#define IPCIDRROUTETABLE_MIN_COL   COLUMN_IPCIDRROUTEDEST
#define IPCIDRROUTETABLE_MAX_COL   COLUMN_IPCIDRROUTESTATUS


    /*
     * TODO:405:r: Review IPCIDRROUTETABLE_SETTABLE_COLS macro.
     * OR together all the writable cols.
     */
#define IPCIDRROUTETABLE_SETTABLE_COLS (COLUMN_IPCIDRROUTEIFINDEX_FLAG | COLUMN_IPCIDRROUTETYPE_FLAG | COLUMN_IPCIDRROUTEINFO_FLAG | COLUMN_IPCIDRROUTENEXTHOPAS_FLAG | COLUMN_IPCIDRROUTEMETRIC1_FLAG | COLUMN_IPCIDRROUTEMETRIC2_FLAG | COLUMN_IPCIDRROUTEMETRIC3_FLAG | COLUMN_IPCIDRROUTEMETRIC4_FLAG | COLUMN_IPCIDRROUTEMETRIC5_FLAG | COLUMN_IPCIDRROUTESTATUS_FLAG)
    /*
     * TODO:405:r: Review IPCIDRROUTETABLE_REQUIRED_COLS macro.
     * OR together all the required rows for row creation.
     * default is writable cols w/out defaults.
     */
#define IPCIDRROUTETABLE_REQUIRED_COLS (COLUMN_IPCIDRROUTETYPE_FLAG | COLUMN_IPCIDRROUTEINFO_FLAG | COLUMN_IPCIDRROUTESTATUS_FLAG)

    /*
     * NOTES on enums
     * ==============
     *
     * Value Mapping
     * -------------
     * If the values for your data type don't exactly match the
     * possible values defined by the mib, you should map them
     * below. For example, a boolean flag (1/0) is usually represented
     * as a TruthValue in a MIB, which maps to the values (1/2).
     *
     */
/*************************************************************************
 *************************************************************************
 *
 * enum definitions for table ipCidrRouteTable
 *
 *************************************************************************
 *************************************************************************/

/*************************************************************
 * constants for enums for the MIB node
 * ipCidrRouteType (INTEGER / ASN_INTEGER)
 *
 * since a Textual Convention may be referenced more than once in a
 * MIB, protect againt redefinitions of the enum values.
 */
#ifndef IPCIDRROUTETYPE_ENUMS
#define IPCIDRROUTETYPE_ENUMS

#define IPCIDRROUTETYPE_OTHER  1
#define IPCIDRROUTETYPE_REJECT  2
#define IPCIDRROUTETYPE_LOCAL  3
#define IPCIDRROUTETYPE_REMOTE  4

#endif                          /* IPCIDRROUTETYPE_ENUMS */


/*************************************************************
 * constants for enums for the MIB node
 * ipCidrRouteProto (INTEGER / ASN_INTEGER)
 *
 * since a Textual Convention may be referenced more than once in a
 * MIB, protect againt redefinitions of the enum values.
 */
#ifndef IPCIDRROUTEPROTO_ENUMS
#define IPCIDRROUTEPROTO_ENUMS

#define IPCIDRROUTEPROTO_OTHER  1
#define IPCIDRROUTEPROTO_LOCAL  2
#define IPCIDRROUTEPROTO_NETMGMT  3
#define IPCIDRROUTEPROTO_ICMP  4
#define IPCIDRROUTEPROTO_EGP  5
#define IPCIDRROUTEPROTO_GGP  6
#define IPCIDRROUTEPROTO_HELLO  7
#define IPCIDRROUTEPROTO_RIP  8
#define IPCIDRROUTEPROTO_ISIS  9
#define IPCIDRROUTEPROTO_ESIS  10
#define IPCIDRROUTEPROTO_CISCOIGRP  11
#define IPCIDRROUTEPROTO_BBNSPFIGP  12
#define IPCIDRROUTEPROTO_OSPF  13
#define IPCIDRROUTEPROTO_BGP  14
#define IPCIDRROUTEPROTO_IDPR  15
#define IPCIDRROUTEPROTO_CISCOEIGRP  16

#endif                          /* IPCIDRROUTEPROTO_ENUMS */


/*************************************************************
 * constants for enums for the MIB node
 * ipCidrRouteStatus (RowStatus / ASN_INTEGER)
 *
 * since a Textual Convention may be referenced more than once in a
 * MIB, protect againt redefinitions of the enum values.
 */
#ifndef ROWSTATUS_ENUMS
#define ROWSTATUS_ENUMS

#define ROWSTATUS_ACTIVE  1
#define ROWSTATUS_NOTINSERVICE  2
#define ROWSTATUS_NOTREADY  3
#define ROWSTATUS_CREATEANDGO  4
#define ROWSTATUS_CREATEANDWAIT  5
#define ROWSTATUS_DESTROY  6

#endif                          /* ROWSTATUS_ENUMS */




#ifdef __cplusplus
}
#endif
#endif                          /* IPCIDRROUTETABLE_OIDS_H */
