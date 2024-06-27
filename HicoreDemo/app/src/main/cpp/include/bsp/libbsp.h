#ifndef __BSP_CORE_INTERFACE_H
#define __BSP_CORE_INTERFACE_H

struct bsp_ethernet_data{
    int mode;
    int phy;
    char ip[128];
    char gateway[128];
    char netmask[128];
    char dns1[128];
    char dns2[128];
};

typedef enum {
    BSP_CORE_ETHERNET_ETH0 = 0,
    BSP_CORE_ETHERNET_ETH1,
}BSP_CORE_ETHERNET_NUM;

typedef enum {
    BSP_CORE_ETHERNET_LINK_STAT = 0,
    BSP_CORE_ETHERNET_SPEED_STAT,
    BSP_CORE_ETHERNET_DHCP_STAT,
}BSP_CORE_ETHERNET_STAT_TYPE;

typedef enum {
    BSP_CORE_ETHERNET_LINK_DOWN = 0,
    BSP_CORE_ETHERNET_LINK_UP,
    BSP_CORE_ETHERNET_SPEED_10M,
    BSP_CORE_ETHERNET_SPEED_100M,
    BSP_CORE_ETHERNET_SPEED_1000M,
    BSP_CORE_ETHERNET_DHCP_ONGOING,
    BSP_CORE_ETHERNET_DHCP_END,
}BSP_CORE_ETHERNET_STAT_VALUE;


int bsp_core_ethernet_set_para(struct bsp_ethernet_data *bsp_data);
int bsp_core_ethernet_get_para(struct bsp_ethernet_data *bsp_data);
int bsp_core_ethernet_get_stat (int eth_num, int stat_type, int *stat_value);
int bsp_core_ethernet_set_single_para (struct bsp_ethernet_data *bsp_data);
int bsp_core_ethernet_get_link_stat(int eth_num, int *value);
int bsp_core_systemui_set_icon(int index, char *icon_name, char *icon_path);
int bsp_core_systemui_cancel_icon(int index,char *icon_name);

#define ERR_NO_ADDRESS -1
#define ERR_CONNECT    -2
#define ERR_SEND       -3
#define ERR_RECV       -4
#define ERR_NETMASK    -5
#define ERR_NO_IP      -6
#define ERR_POINTER    -7

#endif
