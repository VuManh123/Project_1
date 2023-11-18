import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Scanner;
import java.util.TreeMap;

class Submission {
    String userID;
    String problemID;
    String timePoint;
    String status;
    int point;
}
@SuppressWarnings({"unchecked", "deprecation"})
public class AnalyzeCodeSubmission {
    public static void main(String[] args) {
        List<Submission> submissions = new ArrayList<>();
        Map<String, Integer> errorSubmissionCount = new HashMap<>();
        Map<String, TreeMap<Integer, Integer>> maxPointsByUserAndProblem = new HashMap<>();
        List<String> submissionTimes = new ArrayList<>();

        Scanner scanner = new Scanner(System.in);
        while (true) {
            String input = scanner.next();
            if (input.charAt(0) == '#') {
                break;
            }

            Submission submission = new Submission();
            submission.userID = input;
            submission.problemID = scanner.next();
            submission.timePoint = scanner.next();
            submission.status = scanner.next();
            submission.point = scanner.nextInt();
            submissions.add(submission);
            submissionTimes.add(submission.timePoint);

            if (submission.status.equals("ERR")) {
                errorSubmissionCount.put(submission.userID, errorSubmissionCount.getOrDefault(submission.userID, 0) + 1);
            }

            int problemIndex = Integer.parseInt(submission.problemID.substring(1));
            maxPointsByUserAndProblem.computeIfAbsent(submission.userID, k -> new TreeMap<>())
                    .put(problemIndex, Math.max(maxPointsByUserAndProblem.get(submission.userID).getOrDefault(problemIndex, 0), submission.point));
        }

        submissionTimes.sort(null);

        while (true) {
            String query = scanner.next();
            if (query.charAt(0) == '#') {
                break;
            }

            if (query.equals("?total_number_submissions")) {
                System.out.println(submissions.size());
            } else if (query.equals("?number_error_submision")) {
                int numErrorSubmissions = 0;
                for (Submission submission : submissions) {
                    if (submission.status.equals("ERR")) {
                        numErrorSubmissions++;
                    }
                }
                System.out.println(numErrorSubmissions);
            } else if (query.equals("?number_error_submision_of_user")) {
                String targetUserID = scanner.next();
                int numErrorSubmissionsOfUser = errorSubmissionCount.getOrDefault(targetUserID, 0);
                System.out.println(numErrorSubmissionsOfUser);
            } else if (query.equals("?total_point_of_user")) {
                String userID = scanner.next();
                int totalPoint = 0;
                if (maxPointsByUserAndProblem.containsKey(userID)) {
                    for (Map.Entry<Integer, Integer> problem : maxPointsByUserAndProblem.get(userID).entrySet()) {
                        totalPoint += problem.getValue();
                    }
                }
                System.out.println(totalPoint);
            } else if (query.equals("?number_submission_period")) {
                String fromTime = scanner.next();
                String toTime = scanner.next();

                int startTimeIndex = lowerBound(submissionTimes, fromTime);
                int endTimeIndex = upperBound(submissionTimes, toTime);

                int numSubmissionsInPeriod = endTimeIndex - startTimeIndex;
                System.out.println(numSubmissionsInPeriod);
            }
        }
    }

    // Binary search for lower bound
    private static int lowerBound(List<String> list, String value) {
        int left = 0;
        int right = list.size();
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (list.get(mid).compareTo(value) < 0) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }
        return left;
    }

    // Binary search for upper bound
    private static int upperBound(List<String> list, String value) {
        int left = 0;
        int right = list.size();
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (list.get(mid).compareTo(value) <= 0) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }
        return left;
    }
}
