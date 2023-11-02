import java.util.*;
import java.text.ParseException;
import java.text.SimpleDateFormat;

class Submission {
    String userID;
    String problemID;
    Date timePoint;
    String status;
    int point;

    public Submission(String userID, String problemID, Date timePoint, String status, int point) {
        this.userID = userID;
        this.problemID = problemID;
        this.timePoint = timePoint;
        this.status = status;
        this.point = point;
    }
}
@SuppressWarnings({"unchecked", "deprecation"})
public class AnalyzeCodeSubmission {
    public static void main(String[] args) throws ParseException {
        Scanner scanner = new Scanner(System.in);
        List<Submission> submissions = new ArrayList<>();

        // Read and process the first block of data
        String line;
        SimpleDateFormat dateFormat = new SimpleDateFormat("HH:mm:ss");
        while (!(line = scanner.nextLine()).equals("#")) {
            String[] parts = line.split(" ");
            String userID = parts[0];
            String problemID = parts[1];
            Date timePoint = dateFormat.parse(parts[2]);
            String status = parts[3];
            int point = Integer.parseInt(parts[4]);
            submissions.add(new Submission(userID, problemID, timePoint, status, point));
        }

        // Process the queries in the second block
        while (!(line = scanner.nextLine()).equals("#")) {
            if (line.equals("?total_number_submissions")) {
                System.out.println(submissions.size());
            } else if (line.equals("?number_error_submision")) {
                int errorSubmissions = 0;
                for (Submission submission : submissions) {
                    if (submission.status.equals("ERR")) {
                        errorSubmissions++;
                    }
                }
                System.out.println(errorSubmissions);
            } else if (line.startsWith("?number_error_submision_of_user")) {
                String[] parts = line.split(" ");
                String userID = parts[1];
                int errorSubmissions = 0;
                for (Submission submission : submissions) {
                    if (submission.userID.equals(userID) && submission.status.equals("ERR")) {
                        errorSubmissions++;
                    }
                }
                System.out.println(errorSubmissions);
            } else if (line.startsWith("?total_point_of_user")) {
                String[] parts = line.split(" ");
                String userID = parts[1];
                int totalPoints = 0;
                for (Submission submission : submissions) {
                    if (submission.userID.equals(userID)) {
                        totalPoints = Math.max(totalPoints, submission.point);
                    }
                }
                System.out.println(totalPoints);
            } else if (line.startsWith("?number_submission_period")) {
                String[] parts = line.split(" ");
                Date fromTimePoint = dateFormat.parse(parts[1]);
                Date toTimePoint = dateFormat.parse(parts[2]);
                int submissionsInPeriod = 0;
                for (Submission submission : submissions) {
                    if (submission.timePoint.compareTo(fromTimePoint) >= 0 && submission.timePoint.compareTo(toTimePoint) <= 0) {
                        submissionsInPeriod++;
                    }
                }
                System.out.println(submissionsInPeriod);
            }
        }
    }
}
