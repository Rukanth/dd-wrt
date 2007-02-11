/*
 * Note: this file originally auto-generated by mib2c using
 *       version : 1.17 $ of : mfd-data-access.m2c,v $
 *
 * $Id: tcpConnectionTable_data_access.h,v 1.3 2005/12/01 21:42:04 rstory Exp $
 */
#ifndef TCPCONNECTIONTABLE_DATA_ACCESS_H
#define TCPCONNECTIONTABLE_DATA_ACCESS_H

#ifdef __cplusplus
extern          "C" {
#endif


    /*
     *********************************************************************
     * function declarations
     */

    /*
     *********************************************************************
     * Table declarations
     */
/**********************************************************************
 **********************************************************************
 ***
 *** Table tcpConnectionTable
 ***
 **********************************************************************
 **********************************************************************/
    /*
     * TCP-MIB::tcpConnectionTable is subid 19 of tcp.
     * Its status is Current.
     * OID: .1.3.6.1.2.1.6.19, length: 8
     */


    int
     
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        tcpConnectionTable_init_data(tcpConnectionTable_registration *
                                     tcpConnectionTable_reg);


    /*
     * TODO:180:o: Review tcpConnectionTable cache timeout.
     * The number of seconds before the cache times out
     */
#define TCPCONNECTIONTABLE_CACHE_TIMEOUT   60

    void            tcpConnectionTable_container_init(netsnmp_container
                                                      **container_ptr_ptr,
                                                      netsnmp_cache *
                                                      cache);
    void            tcpConnectionTable_container_shutdown(netsnmp_container
                                                          *container_ptr);

    int             tcpConnectionTable_container_load(netsnmp_container
                                                      *container);
    void            tcpConnectionTable_container_free(netsnmp_container
                                                      *container);

    int             tcpConnectionTable_cache_load(netsnmp_container
                                                  *container);
    void            tcpConnectionTable_cache_free(netsnmp_container
                                                  *container);

    int
     
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        tcpConnectionTable_row_prep(tcpConnectionTable_rowreq_ctx *
                                    rowreq_ctx);



#ifdef __cplusplus
}
#endif
#endif                          /* TCPCONNECTIONTABLE_DATA_ACCESS_H */
