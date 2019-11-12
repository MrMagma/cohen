const fs = require("fs");
const PNG = require("pngjs").PNG;

let [,, input, output, size] = process.argv;

size = parseInt(size);

if (!fs.existsSync(input)) {
    console.error("Input file does not exist");
    process.exit(1);
}

let matrix = fs.readFileSync(input, "utf8").split("\n").map(line => line.split(" ").map(c => parseInt(c)));

let outputImg = new PNG({
    width: size * 2,
    height: size * 2,
    filterType: -1,
    colorType: 4
});

function writePixel(x, y, r, g, b, a) {
    let i = (outputImg.width * y + x) << 2;
    outputImg.data[i] = r;
    outputImg.data[i + 1] = g;
    outputImg.data[i + 2] = b;
    outputImg.data[i + 3] = a;
}

for (let i = 0; i < matrix.length; i++) {
    for (let j = 0; j < matrix[i].length; j++) {
        let c = matrix[i][j] * 255;
        let x = (size - i) + 2 * j,
            y = i * 2;
        writePixel(x, y, c, c, c, 255);
        writePixel(x + 1, y, c, c, c, 255);
        writePixel(x, y + 1, c, c, c, 255);
        writePixel(x + 1, y + 1, c, c, c, 255);
    }
}

outputImg.pack().pipe(fs.createWriteStream(output));