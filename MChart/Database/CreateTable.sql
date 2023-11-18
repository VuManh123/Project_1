--I. Tạo bảng 
--1. Tạo bảng teams
CREATE TABLE Teams (
	STT INT IDENTITY(1, 1),
    team_id AS CONVERT(NVARCHAR(10), 'MT' + RIGHT('00000' + CAST(STT AS VARCHAR(5)), 5)) PERSISTED PRIMARY KEY,
    team_name NVARCHAR(255),
    team_description NVARCHAR(MAX)
);

--2. Tạo bảng các user
CREATE TABLE Users (
	STT INT IDENTITY(1, 1),
    userid AS CONVERT(NVARCHAR(10), 'MU' + RIGHT('00000' + CAST(STT AS VARCHAR(5)), 5)) PERSISTED PRIMARY KEY,
    username NVARCHAR(50),
    password NVARCHAR(255),
    email NVARCHAR(100),
    created_at DATETIME
);

-- 3. Tạo bảng projects của các team
CREATE TABLE Projects (
	STT INT IDENTITY(1, 1),
    project_id AS CONVERT(NVARCHAR(10), 'MP' + RIGHT('00000' + CAST(STT AS VARCHAR(5)), 5)) PERSISTED PRIMARY KEY,
    project_name NVARCHAR(255),
    project_description NVARCHAR(MAX),
    team_id NVARCHAR(10) FOREIGN KEY REFERENCES Teams(team_id)
);

-- 4. Tạo bảng biêu đồ trong các projects
CREATE TABLE Charts (
	STT INT IDENTITY(1, 1),
    chart_id AS CONVERT(NVARCHAR(10), 'MC' + RIGHT('00000' + CAST(STT AS VARCHAR(5)), 5)) PERSISTED PRIMARY KEY,
    project_id NVARCHAR(10) FOREIGN KEY REFERENCES Projects(project_id),
    data NVARCHAR(MAX) -- Dữ liệu lưu trữ dưới dạng JSON
);

--5. Một user có thể ở nhiều team tạo bảng user_team
CREATE TABLE User_Teams (
    userid NVARCHAR(10) FOREIGN KEY REFERENCES Users(userid),
    team_id NVARCHAR(10) FOREIGN KEY REFERENCES Teams(team_id),
    role NVARCHAR(50) -- Quyền trong nhóm (quản trị viên, thành viên, v.v.)
);

--6. Bảng lịch sử thay đổi trong các chart
CREATE TABLE Change_History (
	STT INT IDENTITY(1, 1),
    change_id AS CONVERT(NVARCHAR(10), 'MCH' + RIGHT('00000' + CAST(STT AS VARCHAR(5)), 5)) PERSISTED PRIMARY KEY,
    chart_id NVARCHAR(10) FOREIGN KEY REFERENCES Charts(chart_id),
	type_change NVARCHAR(20),
    change_description NVARCHAR(MAX),
	userid NVARCHAR(10) FOREIGN KEY REFERENCES Users(userid), --Thay doi boi ai
    changed_at DATETIME
);


-- II. Insert dữ liệu vào bảng
-- 1. Thêm dữ liệu vào bảng Teams
INSERT INTO Teams (team_name, team_description)
VALUES 
    ('Development Team', 'Team for software development'),
    ('Marketing Team', 'Team for marketing activities'),
    ('Design Team', 'Team for graphic and UI/UX design');

-- 2. Thêm dữ liệu vào bảng Users
INSERT INTO Users (username, password, email, created_at)
VALUES 
    ('john_doe', 'password123', 'john@example.com', GETDATE()),
    ('jane_smith', 'pass456', 'jane@example.com', GETDATE()),
    ('bob_miller', 'pass789', 'bob@example.com', GETDATE());

-- 3. Thêm dữ liệu vào bảng Projects
INSERT INTO Projects (project_name, project_description, team_id)
VALUES 
    ('Web App Development', 'Developing a new web application', 'MT00001'),
    ('Social Media Campaign', 'Marketing campaign on social media', 'MT00002'),
    ('UI/UX Redesign', 'Redesigning the user interface', 'MT00003');

-- 4. Thêm dữ liệu vào bảng Charts
INSERT INTO Charts (project_id, data)
VALUES 
    ('MP00001','{"type":"line","labels":["January","February","March"],"datasets":[{"label":"Sales","data":[50,60,70],"backgroundColor":"rgba(75, 192, 192, 0.2)","borderColor":"rgba(75, 192, 192, 1)","borderWidth":1}]}'),
    ('MP00002','{"type":"bar","labels":["Red","Blue","Yellow"],"datasets":[{"label":"Colors","data":[15,25,10],"backgroundColor":["rgba(255, 99, 132, 0.2)","rgba(54, 162, 235, 0.2)","rgba(255, 255, 0, 0.2)"],"borderColor":["rgba(255,99,132,1)","rgba(54, 162, 235, 1)","rgba(255, 255, 0, 1)"],"borderWidth":1}]}'),
    ('MP00003','{"type":"pie","labels":["Apple","Orange","Banana"],"datasets":[{"label":"Fruits","data":[30,20,15],"backgroundColor":["rgba(255, 99, 132, 0.2)","rgba(255, 165, 0, 0.2)","rgba(255, 255, 0, 0.2)"],"borderColor":["rgba(255,99,132,1)","rgba(255, 165, 0, 1)","rgba(255, 255, 0, 1)"],"borderWidth":1}]}');

-- 5. Thêm dữ liệu vào bảng User_Teams
INSERT INTO User_Teams (userid, team_id, role)
VALUES 
    ('MU00001', 'MT00001', 'Leader'),
    ('MU00002', 'MT00001', 'Member'),
    ('MU00003', 'MT00002', 'Leader'),
    ('MU00001', 'MT00003', 'Leader');

-- 6. Thêm dữ liệu vào bảng Change_History
INSERT INTO Change_History (chart_id, type_change, change_description, userid, changed_at)
VALUES 
    ('MC00001', 'Update', 'Updated sales data', 'MU00001', GETDATE()),
    ('MC00003', 'Insert', 'Inserted new pie chart', 'MU00003', GETDATE());

-- III. Tạo một số trigger
-- 1. Trigger tư set role cho người đầu tiên lập teams
CREATE TRIGGER SetLeaderRoleOnNewTeam
ON Teams
AFTER INSERT
AS
BEGIN
    -- Kiểm tra nếu có bất kỳ dòng mới nào được chèn vào bảng Teams
    IF (SELECT COUNT(*) FROM inserted) > 0
    BEGIN
        -- Lấy ID của team mới được chèn
        DECLARE @newTeamId NVARCHAR(10)
        SELECT @newTeamId = team_id FROM inserted;

        -- Lấy ID của người tạo team mới
        DECLARE @creatorUserId NVARCHAR(10)
        SELECT @creatorUserId = userid FROM User_Teams WHERE team_id = @newTeamId;

        -- Nếu tìm thấy người tạo, thêm một dòng mới vào bảng User_Teams với quyền 'Leader'
        IF (@creatorUserId IS NOT NULL)
        BEGIN
            INSERT INTO User_Teams (userid, team_id, role)
            VALUES (@creatorUserId, @newTeamId, 'Leader');
        END
    END
END;


CREATE TRIGGER AutoAssignMemberRole
ON User_Teams
AFTER INSERT
AS
BEGIN
    -- Kiểm tra nếu có bất kỳ dòng mới nào được chèn vào bảng User_Teams
    IF (SELECT COUNT(*) FROM inserted) > 0
    BEGIN
        DECLARE @teamId NVARCHAR(10);
        DECLARE @userId NVARCHAR(10);

        -- Lấy ID của team mới được chèn
        SELECT @teamId = team_id FROM inserted;

        -- Lấy ID của người dùng mới được chèn
        SELECT @userId = userid FROM inserted;

        -- Kiểm tra role trong bảng User_Teams và gán tự động role cho người dùng
        IF EXISTS (SELECT * FROM User_Teams WHERE team_id = @teamId AND userid = @userId AND role != 'Leader')
        BEGIN
            -- Gán tự động role dựa trên điều kiện nào đó
            DECLARE @role NVARCHAR(50);
            SET @role = 'Member'
            -- Cập nhật role trong bảng User_Teams
            UPDATE User_Teams
            SET role = @role
            WHERE team_id = @teamId AND userid = @userId;
        END
    END
END;

-- Phân role
-- Tạo role Leader và Member
CREATE ROLE Leader;
CREATE ROLE Member;

-- Phân quyền cho role Leader
GRANT SELECT, INSERT, UPDATE, DELETE ON Teams TO Leader;
DENY INSERT, UPDATE, DELETE ON Users TO Leader;
GRANT SELECT, INSERT, UPDATE, DELETE ON Projects TO Leader;
GRANT SELECT, INSERT, UPDATE, DELETE ON Charts TO Leader;
DENY INSERT, UPDATE, DELETE ON Change_History TO Leader;

-- Phân quyền cho role Member
GRANT SELECT, INSERT, UPDATE, DELETE ON Charts TO Member;
GRANT SELECT ON Teams TO Member;
GRANT SELECT ON Projects TO Member;
GRANT SELECT ON Change_History TO Member;
-- Phân quyền cho role Member trên các bảng khác (Teams, Users, Projects)
DENY INSERT, UPDATE, DELETE ON Teams TO Member;
DENY INSERT, UPDATE, DELETE ON Users TO Member;
DENY INSERT, UPDATE, DELETE ON Projects TO Member;
DENY INSERT, UPDATE, DELETE ON Change_History TO Member;