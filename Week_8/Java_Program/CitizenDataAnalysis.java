import java.util.*;
import java.text.ParseException;
import java.text.SimpleDateFormat;

@SuppressWarnings({"unchecked", "deprecation"})
class Citizen {
    String code;
    String dateOfBirth;
    String fatherCode;
    String motherCode;
    char isAlive;
    String regionCode;

    public Citizen(String code, String dateOfBirth, String fatherCode, String motherCode, char isAlive, String regionCode) {
        this.code = code;
        this.dateOfBirth = dateOfBirth;
        this.fatherCode = fatherCode;
        this.motherCode = motherCode;
        this.isAlive = isAlive;
        this.regionCode = regionCode;
    }
}

public class CitizenDataAnalysis {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        ArrayList<Citizen> citizens = new ArrayList<>();
        SimpleDateFormat dateFormat = new SimpleDateFormat("yyyy-MM-dd");

        // Read the citizen data
        while (true) {
            String line = scanner.nextLine().trim();
            if (line.equals("*")) {
                break;
            }
            String[] parts = line.split(" ");
            String code = parts[0];
            String dateOfBirth = parts[1];
            String fatherCode = parts[2];
            String motherCode = parts[3];
            char isAlive = parts[4].charAt(0);
            String regionCode = parts[5];
            citizens.add(new Citizen(code, dateOfBirth, fatherCode, motherCode, isAlive, regionCode));
        }

        // Process queries
        while (true) {
            String query = scanner.nextLine().trim();
            if (query.equals("***")) {
                break;
            }
            String[] queryParts = query.split(" ");
            String command = queryParts[0];
            if (command.equals("NUMBER_PEOPLE")) {
                System.out.println(citizens.size());
            } else if (command.equals("NUMBER_PEOPLE_BORN_AT")) {
                String date = queryParts[1];
                int count = 0;
                for (Citizen citizen : citizens) {
                    if (citizen.dateOfBirth.equals(date)) {
                        count++;
                    }
                }
                System.out.println(count);
            } else if (command.equals("MOST_ALIVE_ANCESTOR")) {
                String code = queryParts[1];
                int generationDistance = findMostAliveAncestor(citizens, code, 0);
                System.out.println(generationDistance);
            } else if (command.equals("NUMBER_PEOPLE_BORN_BETWEEN")) {
                String fromDateStr = queryParts[1];
                String toDateStr = queryParts[2];
                try {
                    Date fromDate = dateFormat.parse(fromDateStr);
                    Date toDate = dateFormat.parse(toDateStr);
                    int count = 0;
                    for (Citizen citizen : citizens) {
                        Date date = dateFormat.parse(citizen.dateOfBirth);
                        if (date.compareTo(fromDate) >= 0 && date.compareTo(toDate) <= 0) {
                            count++;
                        }
                    }
                    System.out.println(count);
                } catch (ParseException e) {
                    e.printStackTrace();
                }
            } else if (command.equals("MAX_UNRELATED_PEOPLE")) {
                int maxUnrelatedPeople = findMaxUnrelatedPeople(citizens);
                System.out.println(maxUnrelatedPeople);
            }
        }
    }

    private static int findMostAliveAncestor(ArrayList<Citizen> citizens, String code, int generationDistance) {
        Citizen currentCitizen = null;
        for (Citizen citizen : citizens) {
            if (citizen.code.equals(code)) {
                currentCitizen = citizen;
                break;
            }
        }

        if (currentCitizen == null) {
            return -1; // Not found
        }

        if (currentCitizen.fatherCode.equals("0000000") && currentCitizen.motherCode.equals("0000000")) {
            return generationDistance;
        }

        int fatherDistance = 0;
        int motherDistance = 0;

        if (!currentCitizen.fatherCode.equals("0000000")) {
            fatherDistance = findMostAliveAncestor(citizens, currentCitizen.fatherCode, generationDistance + 1);
        }

        if (!currentCitizen.motherCode.equals("0000000")) {
            motherDistance = findMostAliveAncestor(citizens, currentCitizen.motherCode, generationDistance + 1);
        }

        return Math.max(fatherDistance, motherDistance);
    }

    private static int findMaxUnrelatedPeople(ArrayList<Citizen> citizens) {
        int n = citizens.size();
        int[] dp = new int[n];

        for (int i = 0; i < n; i++) {
            dp[i] = 1;
            for (int j = 0; j < i; j++) {
                if (citizens.get(i).fatherCode.equals("0000000") && citizens.get(i).motherCode.equals("0000000")
                        && citizens.get(j).fatherCode.equals("0000000") && citizens.get(j).motherCode.equals("0000000")) {
                    dp[i] = Math.max(dp[i], dp[j] + 1);
                }
            }
        }

        int maxUnrelatedPeople = 0;
        for (int i = 0; i < n; i++) {
            maxUnrelatedPeople = Math.max(maxUnrelatedPeople, dp[i]);
        }

        return maxUnrelatedPeople;
    }
}

