const express = require("express");
const cors = require("cors");
const { spawn } = require("child_process");

const app = express();

app.use(cors());
app.use(express.json());

app.post("/calculate", (req, res) => {
  const { expression } = req.body;

  if (!expression) {
    return res.status(400).json({ error: "expression is required" });
  }

  const cpp = spawn("./calc");

  let output = "";
  let errorOutput = "";

  cpp.stdout.on("data", (data) => {
    output += data.toString();
  });

  cpp.stderr.on("data", (data) => {
    errorOutput += data.toString();
  });

  cpp.on("close", (code) => {
    if (code !== 0) {
      return res.status(500).json({
        error: "C++ program failed",
        details: errorOutput,
      });
    }

    const result = output.trim();
    return res.json({ result });
  });

  cpp.stdin.write(expression + "\n");
  cpp.stdin.end();
});
const PORT = process.env.PORT || 3000;
app.listen(PORT, () => {
  console.log("✅ Server running on port" + PORT);
});
