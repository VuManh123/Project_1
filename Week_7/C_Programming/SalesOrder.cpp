//C 
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

struct Revenue {
    char shopID[11];
    char customerID[11];
    int totalRevenue;
};

struct Shop {
    int totalRevenue;
};

int hash(const char* key) {
    int sum = 0;
    for (int i = 0; key[i] != '\0'; i++) {
        sum += key[i];
    }
    return sum % 100000;
}

int main() {
    struct SalesOrder* salesOrders = (struct SalesOrder*)malloc(100000 * sizeof(struct SalesOrder));
    struct Revenue** revenue = (struct Revenue**)malloc(100000 * sizeof(struct Revenue*));
    for (int i = 0; i < 100000; i++) {
        revenue[i] = (struct Revenue*)malloc(100000 * sizeof(struct Revenue));
    }
    struct Shop* shopMap = (struct Shop*)malloc(100000 * sizeof(struct Shop));

    int numOrders = 0;

    char input[100];
    while (1) {
        scanf("%s", input);
        if (input[0] == '#') {
            break;
        }

        struct SalesOrder order;
        strcpy(order.customerID, input);
        scanf("%s %d %s %s", order.productID, &order.price, order.shopID, order.timePoint);
        salesOrders[numOrders] = order;

        int customerHash = hash(order.customerID);
        int shopHash = hash(order.shopID);

        // Update revenue
        strcpy(revenue[customerHash][shopHash].shopID, order.shopID);
        strcpy(revenue[customerHash][shopHash].customerID, order.customerID);
        revenue[customerHash][shopHash].totalRevenue += order.price;

        // Update shopMap
        shopMap[shopHash].totalRevenue += order.price;

        numOrders++;
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
            int totalRevenue = 0;
            for (int i = 0; i < numOrders; i++) {
                totalRevenue += salesOrders[i].price;
            }
            printf("%d\n", totalRevenue);
        } else if (strstr(query, "?revenue_of_shop") != NULL) {
            char shopID[11];
            scanf("%s", shopID);
            int shopHash = hash(shopID);
            printf("%d\n", shopMap[shopHash].totalRevenue);
        } else if (strstr(query, "?total_consume_of_customer_shop") != NULL) {
            char customerID[11];
            char shopID[11];
            scanf("%s %s", customerID, shopID);
            int customerHash = hash(customerID);
            int shopHash = hash(shopID);
            printf("%d\n", revenue[customerHash][shopHash].totalRevenue);
        } else if (strstr(query, "?total_revenue_in_period") != NULL) {
            char fromTime[9];
            char toTime[9];
            scanf("%s %s", fromTime, toTime);
            int periodRevenue = 0;
            for (int i = 0; i < numOrders; i++) {
                if (strcmp(salesOrders[i].timePoint, fromTime) >= 0 && strcmp(salesOrders[i].timePoint, toTime) <= 0) {
                    periodRevenue += salesOrders[i].price;
                }
            }
            printf("%d\n", periodRevenue);
        }
    }

    free(salesOrders);

    // Free memory for 2D array revenue
    for (int i = 0; i < 100000; i++) {
        free(revenue[i]);
    }
    free(revenue);

    free(shopMap);

    return 0;
}

