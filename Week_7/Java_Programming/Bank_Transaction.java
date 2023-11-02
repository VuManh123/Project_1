import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;
import java.util.HashSet;
import java.util.List;
import java.util.ArrayList;
import java.util.Collections;

public class Bank_Transaction {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        // Sử dụng danh sách để lưu trữ giao dịch
        List<Transaction> transactions = new ArrayList<>();
        // Sử dụng HashMap để lưu trữ thông tin tài khoản
        Map<String, Account> accounts = new HashMap<>();

        while (true) {
            String line = scanner.nextLine().trim();
            if (line.equals("#")) {
                break;
            }

            String[] parts = line.split(" ");
            String fromAccount = parts[0];
            String toAccount = parts[1];
            int money = Integer.parseInt(parts[2]);
            transactions.add(new Transaction(fromAccount, toAccount, money));

            if (accounts.containsKey(fromAccount)) {
                accounts.get(fromAccount).addMoneySent(money);
            } else {
                accounts.put(fromAccount, new Account(fromAccount, money, 0));
            }

            if (accounts.containsKey(toAccount)) {
                accounts.get(toAccount).addMoneyReceived(money);
            } else {
                accounts.put(toAccount, new Account(toAccount, 0, money));
            }
        }

        while (true) {
            String query = scanner.nextLine().trim();
            if (query.equals("#")) {
                break;
            }

            if (query.equals("?number_transactions")) {
                System.out.println(transactions.size());
            } else if (query.equals("?total_money_transaction")) {
                int totalMoney = transactions.stream().mapToInt(Transaction::getMoney).sum();
                System.out.println(totalMoney);
            } else if (query.equals("?list_sorted_accounts")) {
                List<String> sortedAccounts = new ArrayList<>(accounts.keySet());
                Collections.sort(sortedAccounts);
                for (String account : sortedAccounts) {
                    System.out.print(account + " ");
                }
                System.out.println();
            } else if (query.startsWith("?total_money_transaction_from")) {
                String accountToFind = query.substring(query.lastIndexOf(" ") + 1);
                Account account = accounts.get(accountToFind);
                if (account != null) {
                    System.out.println(account.getMoneySent());
                } else {
                    System.out.println(0);
                }
            } else if (query.startsWith("?inspect_cycle")) {
                String[] parts = query.split(" ");
                String startAccount = parts[1];
                int k = Integer.parseInt(parts[2]);
                boolean hasCycle = hasTransactionCycle(transactions, startAccount, k, new HashSet<>(), startAccount);
                System.out.println(hasCycle ? "1" : "0");
            }
        }
    }

    private static boolean hasTransactionCycle(
            List<Transaction> transactions, String currentAccount, int k, HashSet<String> visited, String startAccount) {
        if (k == 0) {
            return currentAccount.equals(startAccount);
        }
        if (visited.contains(currentAccount)) {
            return false;
        }

        visited.add(currentAccount);

        for (Transaction transaction : transactions) {
            if (transaction.getFromAccount().equals(currentAccount)) {
                if (hasTransactionCycle(transactions, transaction.getToAccount(), k - 1, visited, startAccount)) {
                    return true;
                }
            }
        }

        visited.remove(currentAccount); // Remove the account from the visited set when backtracking
        return false;
    }
}

class Transaction {
    private String fromAccount;
    private String toAccount;
    private int money;

    public Transaction(String fromAccount, String toAccount, int money) {
        this.fromAccount = fromAccount;
        this.toAccount = toAccount;
        this.money = money;
    }

    public String getFromAccount() {
        return fromAccount;
    }

    public String getToAccount() {
        return toAccount;
    }

    public int getMoney() {
        return money;
    }
}

class Account {
    private String accountNumber;
    private int moneySent;
    private int moneyReceived;

    public Account(String accountNumber, int moneySent, int moneyReceived) {
        this.accountNumber = accountNumber;
        this.moneySent = moneySent;
        this.moneyReceived = moneyReceived;
    }

    public void addMoneySent(int money) {
        moneySent += money;
    }

    public void addMoneyReceived(int money) {
        moneyReceived += money;
    }

    public int getMoneySent() {
        return moneySent;
    }
}
