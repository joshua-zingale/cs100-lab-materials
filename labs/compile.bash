
for dir in */; do
    
    filename=${dir%/}

    slide_file_name="slides.md"
    
    input_file="$filename/$slide_file_name"
    
    if [[ -f "$input_file" ]]; then
        echo "Processing: $filename/$slide_file_name"
        
        pandoc -t beamer -s "$input_file" -o "$filename.pdf"
        
        if [[ $? -eq 0 ]]; then
            echo "Success: Created $filename.pdf"
        else
            echo "Error: Pandoc failed in $filename/$slide_file_name"
        fi
        echo "-----------------------------------"
    fi
done

echo "Complete."
