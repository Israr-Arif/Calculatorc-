    const display = document.getElementById("display");

    function press(val){
      display.value += val;
    }

    function clearDisplay(){
      display.value = "";
    }

    function backspace(){
      display.value = display.value.slice(0, -1);
    }

    // Optional: keyboard support
    document.addEventListener("keydown", (e) => {
      if(e.key === "Enter") calculate();
      if(e.key === "Backspace") backspace();
    });

    async function calculate(){
      let expression = display.value;

      // ✅ frontend percent support: 50% => 0.5
      expression = expression.replaceAll("%", "/100");

      try {
        const res = await fetch("https://calculatorc-1.onrender.com/", {
          method: "POST",
          headers: { "Content-Type": "application/json" },
          body: JSON.stringify({ expression })
        });

        const data = await res.json();

        if(data.result !== undefined){
          display.value = data.result;
        } else {
          display.value = "Error";
        }
      } catch (err) {
        display.value = "Server Error";
      }
    }
    function convertUnit(){
  const value = parseFloat(document.getElementById("convValue").value);
  const type = document.getElementById("convType").value;
  const resultBox = document.getElementById("convResult");

  if(isNaN(value)){
    resultBox.innerText = "❌ Please enter a value";
    return;
  }

  let result = 0;
  let unit = "";

  switch(type){
    case "cm_to_mm": result = value * 10; unit="mm"; break;
    case "mm_to_cm": result = value / 10; unit="cm"; break;

    case "m_to_cm": result = value * 100; unit="cm"; break;
    case "cm_to_m": result = value / 100; unit="m"; break;

    case "km_to_m": result = value * 1000; unit="m"; break;
    case "m_to_km": result = value / 1000; unit="km"; break;

    case "inch_to_cm": result = value * 2.54; unit="cm"; break;
    case "cm_to_inch": result = value / 2.54; unit="inch"; break;

    case "ft_to_m": result = value * 0.3048; unit="m"; break;
    case "m_to_ft": result = value / 0.3048; unit="ft"; break;
  }

  resultBox.innerText = `✅ Result: ${result} ${unit}`;
}

function clearConverter(){
  document.getElementById("convValue").value = "";
  document.getElementById("convResult").innerText = "";
}
function showPage(pageId){
  document.getElementById("calcPage").classList.add("hidden");
  document.getElementById("convPage").classList.add("hidden");

  document.getElementById(pageId).classList.remove("hidden");

  // active button highlight
  const tabs = document.querySelectorAll(".tab");
  tabs.forEach(t => t.classList.remove("active"));

  if(pageId === "calcPage") tabs[0].classList.add("active");
  if(pageId === "convPage") tabs[1].classList.add("active");
}
