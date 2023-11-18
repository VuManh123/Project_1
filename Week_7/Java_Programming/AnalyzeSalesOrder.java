import java.io.*;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.*;

class Order {
    String customerID;
    String productID;
    int price;
    String shopID;
    Date timePoint;

    public Order(String customerID, String productID, int price, String shopID, Date timePoint) {
        this.customerID = customerID;
        this.productID = productID;
        this.price = price;
        this.shopID = shopID;
        this.timePoint = timePoint;
    }
}

public class AnalyzeSalesOrder {
    public static void main(String[] args) throws ParseException {
        List<Order> orders = new ArrayList<>();
        SimpleDateFormat dateFormat = new SimpleDateFormat("HH:mm:ss");

        // Sử dụng HashMap để lưu trữ thông tin đơn đặt hàng theo cửa hàng
        Map<String, List<Order>> ordersByShop = new HashMap<>();

        try (BufferedReader reader = new BufferedReader(new InputStreamReader(System.in))) {
            String line;
            while ((line = reader.readLine()) != null) {
                if (line.equals("#")) {
                    break;
                }
                String[] parts = line.split(" ");
                String customerID = parts[0];
                String productID = parts[1];
                int price = Integer.parseInt(parts[2]);
                String shopID = parts[3];
                Date timePoint = dateFormat.parse(parts[4]);
                Order order = new Order(customerID, productID, price, shopID, timePoint);
                orders.add(order);

                // Cập nhật thông tin đơn đặt hàng theo cửa hàng
                ordersByShop.computeIfAbsent(shopID, k -> new ArrayList<>()).add(order);
            }

            while ((line = reader.readLine()) != null) {
                if (line.equals("#")) {
                    break;
                }

                if (line.equals("?total_number_orders")) {
                    // Số đơn đặt hàng
                    System.out.println(orders.size());
                } else if (line.equals("?total_revenue")) {
                    // Tổng doanh thu
                    int totalRevenue = orders.stream().mapToInt(order -> order.price).sum();
                    System.out.println(totalRevenue);
                } else if (line.startsWith("?revenue_of_shop")) {
                    // Doanh thu của cửa hàng
                    String[] parts = line.split(" ");
                    String shopID = parts[1];
                    List<Order> shopOrders = ordersByShop.get(shopID);
                    if (shopOrders != null) {
                        int shopRevenue = shopOrders.stream().mapToInt(order -> order.price).sum();
                        System.out.println(shopRevenue);
                    } else {
                        System.out.println(0);
                    }
                } else if (line.startsWith("?total_consume_of_customer_shop")) {
                    // Doanh thu Khách hàng - Cửa hàng
                    String[] parts = line.split(" ");
                    String customerID = parts[1];
                    String shopID = parts[2];
                    List<Order> customerShopOrders = ordersByShop.get(shopID);
                    if (customerShopOrders != null) {
                        int customerShopRevenue = customerShopOrders.stream()
                                .filter(order -> order.customerID.equals(customerID))
                                .mapToInt(order -> order.price)
                                .sum();
                        System.out.println(customerShopRevenue);
                    } else {
                        System.out.println(0);
                    }
                } else if (line.startsWith("?total_revenue_in_period")) {
                    // Tổng doanh thu trong khoảng thời gian
                    String[] parts = line.split(" ");
                    Date fromTime = dateFormat.parse(parts[1]);
                    Date toTime = dateFormat.parse(parts[2]);

                    int periodRevenue = orders.stream()
                            .filter(order -> order.timePoint.compareTo(fromTime) >= 0 && order.timePoint.compareTo(toTime) <= 0)
                            .mapToInt(order -> order.price)
                            .sum();
                    System.out.println(periodRevenue);
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
