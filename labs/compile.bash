directories=${1:-*/}
for dir in $directories; do
    
    foldername=${dir%/}

    slide_file_name="slides.md"
    
    input_file="$foldername/$slide_file_name"
    
    if [[ -f "$input_file" ]]; then
        echo "Processing: $foldername/$slide_file_name"

        
        pandoc -t beamer -s "$input_file" \
		-o "$foldername.pdf" \
	    --metadata date="`date "+%B %-d, %Y"`" \
        -V theme:Warsaw \
        --resource-path $foldername
        
        if [[ $? -eq 0 ]]; then
            echo "Success: Created $foldername.pdf"
        else
            echo "Error: Pandoc failed in $foldername/$slide_file_name"
        fi
        echo "-----------------------------------"
    fi
done

echo "Complete."
