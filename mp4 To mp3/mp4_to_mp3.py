from moviepy.editor import VideoFileClip

def convert_mp4_to_mp3(input_file, output_file):
    try:
        # Load the video clip
        video_clip = VideoFileClip(input_file)

        # Extract audio from the video clip
        audio_clip = video_clip.audio

        # Save the audio as an MP3 file
        audio_clip.write_audiofile(output_file)

        # Close the video clip and audio clip objects
        audio_clip.close()
        video_clip.close()

        print(f"Conversion successful! {input_file} converted to {output_file}")

    except Exception as e:
        print(f"Error during conversion: {e}")

if __name__ == "__main__":
    input_file_path = "nm.mp4"
    output_file_path = "panday.mp3"

    convert_mp4_to_mp3(input_file_path, output_file_path)
