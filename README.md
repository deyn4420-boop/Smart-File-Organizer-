𝑺𝒎𝒂𝒓𝒕 𝑭𝒊𝒍𝒆 𝑶𝒓𝒈𝒂𝒏𝒊𝒛𝒆𝒓

A command-line utility built in C++17 that automatically organizes files into category-based folders using the <filesystem> library.

𝐎𝐯𝐞𝐫𝐯𝐢𝐞𝐰

Smart File Organizer scans a directory, identifies files based on their extensions, and moves them into appropriate folders such as Documents, Images, Videos, Executables, and Others.

The tool is designed with safety features like duplicate handling, dry-run preview, hidden file filtering, and operation logging.

𝗙𝗲𝗮𝘁𝘂𝗿𝗲𝘀

• Organizes files by extension

• Automatically creates category folders

• Supports command-line directory input

• Dry-run mode (preview without moving files)

• Prevents overwriting using auto-renaming (file(1).txt)

• Skips hidden and system files

• Logs all operations to organizer.log

• Displays summary of moved and skipped files

𝗖𝗮𝘁𝗲𝗴𝗼𝗿𝗶𝗲𝘀

Category	     Extensions
Documents	    .pdf, .docx, .txt, .md
Images	        .jpg, .jpeg, .png
Videos	        .mp4, .mkv
Executables	    .exe
Others	        All remaining files


𝗥𝗲𝗾𝘂𝗶𝗿𝗲𝗺𝗲𝗻𝘁𝘀

C++17 compatible compiler (MinGW / g++)

Windows / Linux / macOS (filesystem supported)