using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace frontend.utils
{
    internal class Utils
    {
        public static string StringToBinary(string input)
        {
            byte[] bytes = Encoding.ASCII.GetBytes(input);
            StringBuilder binary = new StringBuilder();

            foreach (byte b in bytes)
            {
                binary.Append(Convert.ToString(b, 2).PadLeft(8, '0'));
            }

            return binary.ToString();
        }


        public static string GetBytesFromBinaryString(string binary)
        {
            List<byte> bytes = new List<byte>();
            StringBuilder byteBuilder = new StringBuilder(8); // StringBuilder to accumulate binary digits for each byte

            // Iterate over the binary string
            foreach (char bit in binary)
            {
                byteBuilder.Append(bit); // Append the current binary digit to the StringBuilder

                // If the StringBuilder has accumulated 8 binary digits (representing a byte), convert it to a byte and add to the list
                if (byteBuilder.Length == 8)
                {
                    if (Convert.ToByte(byteBuilder.ToString(), 2) == '}') { break; }

                    bytes.Add(Convert.ToByte(byteBuilder.ToString(), 2)); // Convert binary string to byte and add to list
                    byteBuilder.Clear(); // Clear the StringBuilder for the next byte
                }
            }

            // If the StringBuilder has any remaining binary digits, pad it with zeros and convert to a byte
            if (byteBuilder.Length > 0)
            {
                byteBuilder.Append('0', 8 - byteBuilder.Length); // Pad with zeros if necessary
                bytes.Add(Convert.ToByte(byteBuilder.ToString(), 2)); // Convert binary string to byte and add to list
            }

            return Encoding.Default.GetString(bytes.ToArray()); // Convert list of bytes to an array and return
        }
    }
}
