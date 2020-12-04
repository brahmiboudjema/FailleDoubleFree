/**
 * section: Information
 * synopsis: Extract information about Xen domain 0
 * purpose: Demonstrate the basic use of the library to connect to the
 *          hypervisor and extract domain information.
 * usage: info1
 * test: info1
 * copy: see Copyright for the status of this software.
 */

#include <stdio.h>
#include <stdlib.h>
#include <libvirt/libvirt.h>

/**
 * getDomainInfo:
 * @name: the name of the domain
 *
 * extract the domain 0 information
 */
static void
getDomainInfo(const char *uri, const char *name)
{
    virConnectPtr conn = NULL; /* the hypervisor connection */
    virDomainPtr dom = NULL;   /* the domain being checked */
    virDomainInfo info;        /* the information being fetched */
    int ret;

    conn = virConnectOpen(uri);
    if (conn == NULL) {
        fprintf(stderr, "Failed to connect to hypervisor\n");
        goto error;
    }

    /* Find the domain of the given name */
    dom = virDomainLookupByName(conn, name);
    if (dom == NULL) {
        fprintf(stderr, "Failed to find Domain %s\n", name);
        goto error;
    }

    /* Get the information */
    ret = virDomainGetInfo(dom, &info);
    if (ret < 0) {
        fprintf(stderr, "Failed to get information for Domain %s\n", name);
        goto error;
    }
    
    /* Get Iface information */
    virDomainInterfacePtr *ifaces = NULL;
    int ifaces_count = 0;
    size_t i, j;

    if ((ifaces_count = virDomainInterfaceAddresses(dom, &ifaces, VIR_DOMAIN_INTERFACE_ADDRESSES_SRC_AGENT, 0)) < 0)
        goto cleanup;
    
    for (i = 0; i < ifaces_count; i++) {
        printf("name: %s", ifaces[i]->name);
        if (ifaces[i]->hwaddr)
            printf(" hwaddr: %s", ifaces[i]->hwaddr);

        for (j = 0; j < ifaces[i]->naddrs; j++) {
            virDomainIPAddressPtr ip_addr = ifaces[i]->addrs + j;
            printf("[addr: %s prefix: %d type: %d]",
                ip_addr->addr, ip_addr->prefix, ip_addr->type);
    }
    printf("\n");
}

cleanup:
    if (ifaces && ifaces_count > 0)
        for (i = 0; i < ifaces_count; i++)
            virDomainInterfaceFree(ifaces[i]);
    free(ifaces);

    printf("Domain %s: %d CPUs\n", name, info.nrVirtCpu);

 error:
    if (dom != NULL)
        virDomainFree(dom);
    if (conn != NULL)
        virConnectClose(conn);
}

int main(int argc, char **argv)
{
    if (argc != 3) {
        fprintf(stderr, "syntax: %s: URI NAME\n", argv[0]);
        return 1;
    }
    getDomainInfo(argv[1], argv[2]);

    return 0;
}
