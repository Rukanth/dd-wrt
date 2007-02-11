/*
 * Note: this file originally auto-generated by mib2c using
 *       version : 1.67 $ of : mfd-interface.m2c,v $
 *
 * $Id: tcpConnectionTable_interface.h,v 1.5 2006/01/25 16:25:57 dts12 Exp $
 */
/** @ingroup interface Routines to interface to Net-SNMP
 *
 * \warning This code should not be modified, called directly,
 *          or used to interpret functionality. It is subject to
 *          change at any time.
 * 
 * @{
 */
/*
 * *********************************************************************
 * *********************************************************************
 * *********************************************************************
 * ***                                                               ***
 * ***  NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE  ***
 * ***                                                               ***
 * ***                                                               ***
 * ***       THIS FILE DOES NOT CONTAIN ANY USER EDITABLE CODE.      ***
 * ***                                                               ***
 * ***                                                               ***
 * ***       THE GENERATED CODE IS INTERNAL IMPLEMENTATION, AND      ***
 * ***                                                               ***
 * ***                                                               ***
 * ***    IS SUBJECT TO CHANGE WITHOUT WARNING IN FUTURE RELEASES.   ***
 * ***                                                               ***
 * ***                                                               ***
 * *********************************************************************
 * *********************************************************************
 * *********************************************************************
 */
#ifndef TCPCONNECTIONTABLE_INTERFACE_H
#define TCPCONNECTIONTABLE_INTERFACE_H

#ifdef __cplusplus
extern          "C" {
#endif


#include "tcpConnectionTable.h"


    /*
     ********************************************************************
     * Table declarations
     */

    /*
     * PUBLIC interface initialization routine 
     */
    void
     
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        _tcpConnectionTable_initialize_interface
        (tcpConnectionTable_registration * user_ctx, u_long flags);
    void
     
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        _tcpConnectionTable_shutdown_interface
        (tcpConnectionTable_registration * user_ctx);

         
         
         
         
         
         
        tcpConnectionTable_registration
        * tcpConnectionTable_registration_get(void);

         
         
         
         
         
         
        tcpConnectionTable_registration
        * tcpConnectionTable_registration_set
        (tcpConnectionTable_registration * newreg);

    netsnmp_container *tcpConnectionTable_container_get(void);
    int             tcpConnectionTable_container_size(void);

    u_int           tcpConnectionTable_dirty_get(void);
    void            tcpConnectionTable_dirty_set(u_int status);

         
         
         
         
         
         
        tcpConnectionTable_rowreq_ctx
        * tcpConnectionTable_allocate_rowreq_ctx(tcpConnectionTable_data *,
                                                 void *);
    void
     
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        tcpConnectionTable_release_rowreq_ctx(tcpConnectionTable_rowreq_ctx
                                              * rowreq_ctx);

    int             tcpConnectionTable_index_to_oid(netsnmp_index *
                                                    oid_idx,
                                                    tcpConnectionTable_mib_index
                                                    * mib_idx);
    int             tcpConnectionTable_index_from_oid(netsnmp_index *
                                                      oid_idx,
                                                      tcpConnectionTable_mib_index
                                                      * mib_idx);

    /*
     * access to certain internals. use with caution!
     */
    void
     
        
        
        
        
        
        
        
        
        
             tcpConnectionTable_valid_columns_set(netsnmp_column_info *vc);


#ifdef __cplusplus
}
#endif
#endif                          /* TCPCONNECTIONTABLE_INTERFACE_H */
/**  @} */

