#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct SalesOrder {
    char customerID[11];
    char productID[11];
    int price;
    char shopID[11];
    char timePoint[9];
};

// Hàm nh?p thông tin ðõn ð?t hàng
void inputSalesOrder(struct SalesOrder *order) {
    char input[100];
    scanf("%s", input);
    strcpy(order->customerID, input);
    scanf("%s %d %s %s", order->productID, &order->price, order->shopID, order->timePoint);
}

// Hàm tính t?ng doanh thu c?a hàng c? th?
int calculateShopRevenue(struct SalesOrder salesOrders[], int numOrders, char shopID[11]) {
    int shopRevenue = 0;
    for (int i = 0; i < numOrders; i++) {
        if (strcmp(salesOrders[i].shopID, shopID) == 0) {
            shopRevenue += salesOrders[i].price;
        }
    }
    return shopRevenue;
}

// Hàm tính t?ng doanh thu c?a khách hàng t?i c?a hàng c? th?
int calculateCustomerShopRevenue(struct SalesOrder salesOrders[], int numOrders, char customerID[11], char shopID[11]) {
    int customerShopRevenue = 0;
    for (int i = 0; i < numOrders; i++) {
        if (strcmp(salesOrders[i].customerID, customerID) == 0 && strcmp(salesOrders[i].shopID, shopID) == 0) {
            customerShopRevenue += salesOrders[i].price;
        }
    }
    return customerShopRevenue;
}

// Hàm tính t?ng doanh thu trong kho?ng th?i gian c? th?
int calculateRevenueInPeriod(struct SalesOrder salesOrders[], int numOrders, char fromTime[9], char toTime[9]) {
    int periodRevenue = 0;
    for (int i = 0; i < numOrders; i++) {
        if (strcmp(salesOrders[i].timePoint, fromTime) >= 0 && strcmp(salesOrders[i].timePoint, toTime) <= 0) {
            periodRevenue += salesOrders[i].price;
        }
    }
    return periodRevenue;
}

// Hàm chính
int main() {
    struct SalesOrder salesOrders[100000];
    int numOrders = 0;
    int totalRevenue = 0;
    int totalRevenueShop = 0;

    char input[100];
    while (1) {
        scanf("%s", input);
        if (input[0] == '#') {
            break;
        }

        struct SalesOrder order;
        inputSalesOrder(&order);
        salesOrders[numOrders++] = order;
        totalRevenue += order.price;
        totalRevenueShop += order.price;
    }

    char query[50];
    while (1) {
        scanf("%s", query);
        if (query[0] == '#') {
            break;
        }

        if (strcmp(query, "?total_number_orders") == 0) {
            printf("%d\n", numOrders);
        } else if (strcmp(query, "?total_revenue") == 0) {
            printf("%d\n", totalRevenue);
        } else if (strstr(query, "?revenue_of_shop") != NULL) {
            char shopID[11];
            scanf("%s", shopID);
            int shopRevenue = calculateShopRevenue(salesOrders, numOrders, shopID);
            printf("%d\n", shopRevenue);
        } else if (strstr(query, "?total_consume_of_customer_shop") != NULL) {
            char customerID[11];
            char shopID[11];
            scanf("%s %s", customerID, shopID);
            int customerShopRevenue = calculateCustomerShopRevenue(salesOrders, numOrders, customerID, shopID);
            printf("%d\n", customerShopRevenue);
        } else if (strstr(query, "?total_revenue_in_period") != NULL) {
            char fromTime[9];
            char toTime[9];
            scanf("%s %s", fromTime, toTime);
            int periodRevenue = calculateRevenueInPeriod(salesOrders, numOrders, fromTime, toTime);
            printf("%d\n", periodRevenue);
        }
    }

    return 0;
}

