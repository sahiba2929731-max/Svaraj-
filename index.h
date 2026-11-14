
<!DOCTYPE html>
<html lang="hi">
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width,initial-scale=1">
<meta name="theme-color" content="#07101f">
<title>SWARAJ GALAXY X</title>

<link rel="stylesheet"
 href="https://unpkg.com/leaflet@1.9.4/dist/leaflet.css">

<style>
*{box-sizing:border-box}
body{
 margin:0;background:#07101f;color:#eaf3ff;
 font-family:Arial, sans-serif;
}
header{
 padding:20px 14px;text-align:center;
 background:linear-gradient(120deg,#101d3b,#172e50);
 border-bottom:1px solid #385274;
}
.logo{font-size:27px;font-weight:900;color:#f5c96b;letter-spacing:2px}
.sub{font-size:12px;color:#a9bdd9;margin-top:7px}
.container{max-width:1200px;margin:auto;padding:14px}
.status{
 display:flex;gap:8px;flex-wrap:wrap;margin-bottom:12px
}
.badge{
 background:#122747;border:1px solid #31547c;
 border-radius:20px;padding:8px 11px;
 font-size:12px;color:#76e8dc
}
.panel{
 background:#101d34;border:1px solid #263e60;
 border-radius:14px;padding:14px;margin-bottom:13px;
}
h2{font-size:17px;color:#f5c96b;margin:0 0 12px}
h3{font-size:14px;color:#a9d9ff}
.stats{
 display:grid;grid-template-columns:repeat(4,1fr);gap:9px;
}
.stat{
 background:#09162a;border:1px solid #294362;
 padding:12px;border-radius:10px;min-width:0
}
.stat small{color:#91a9c8;font-size:11px}
.stat strong{display:block;font-size:21px;margin-top:6px;color:#65e4dc}
#map{height:420px;border-radius:12px;z-index:1}
input,select,button{
 padding:11px;border-radius:9px;border:1px solid #345071;
 background:#09162a;color:white;font-size:14px;
}
input{width:100%;min-width:0}
button{cursor:pointer}
button.primary{
 background:linear-gradient(100deg,#b27b24,#f5cc70);
 color:#17120a;border:0;font-weight:bold
}
.controls{display:flex;gap:8px;flex-wrap:wrap}
.controls input{flex:1}
table{width:100%;border-collapse:collapse;font-size:12px}
th,td{padding:10px 6px;border-bottom:1px solid #263e60;text-align:left}
th{color:#f5c96b}
tr{cursor:pointer}
tr:hover{background:#1b3150}
#details{line-height:1.9;color:#b9cbe4}
.note{font-size:12px;color:#9aafcb;line-height:1.6}
footer{text-align:center;color:#7891b3;font-size:12px;padding:20px}
@media(max-width:650px){
 .stats{grid-template-columns:repeat(2,1fr)}
 #map{height:350px}
 .logo{font-size:21px}
 table{font-size:10px}
}
</style>
</head>

<body>
<header>
 <div class="logo">🛰️ SWARAJ GALAXY X</div>
 <div class="sub">INDEPENDENT DIGITAL SPACE NETWORK</div>
 <div class="sub">REAL ORBIT DATA • SGP4 ENGINE • LIVE TRACKING</div>
</header>

<div class="container">

 <div class="status">
  <span class="badge" id="connection">● INITIALIZING</span>
  <span class="badge">PUBLIC ORBIT DATA</span>
  <span class="badge">SGP4 ENGINE</span>
  <span class="badge">DIGITAL MISSION CONTROL</span>
 </div>

 <div class="panel">
  <h2>MISSION STATISTICS</h2>
  <div class="stats">
   <div class="stat"><small>TRACKED OBJECTS</small><strong id="total">0</strong></div>
   <div class="stat"><small>SELECTED ALTITUDE</small><strong id="altitude">--</strong></div>
   <div class="stat"><small>ORBIT SPEED</small><strong id="speed">--</strong></div>
   <div class="stat"><small>CALCULATION STATUS</small><strong id="engineStatus">WAIT</strong></div>
  </div>
 </div>

 <div class="panel">
  <h2>🌍 LIVE EARTH ORBIT MAP</h2>
  <div id="map"></div>
  <p class="note">
   मानचित्र पर बिंदु उपग्रहों की गणना की गई पृथ्वी-स्थितियाँ हैं।
   यह वास्तविक समय की स्थिति का अनुमान है, लाइव कैमरा दृश्य नहीं।
  </p>
 </div>

 <div class="panel">
  <h2>🔭 SATELLITE CONTROL</h2>
  <div class="controls">
   <input id="search" placeholder="नाम या NORAD नंबर खोजें">
   <button onclick="filterSatellites()">SEARCH</button>
   <button class="primary" onclick="loadData()">UPDATE DATA</button>
  </div>
  <p class="note" id="dataStatus">डेटा लोड होने की प्रतीक्षा...</p>
 </div>

 <div class="panel">
  <h2>📡 SELECTED SATELLITE</h2>
  <div id="details">मानचित्र या सूची से उपग्रह चुनें।</div>
 </div>

 <div class="panel">
  <h2>🛰️ TRACKED SATELLITES</h2>
  <div style="overflow-x:auto">
   <table>
    <thead>
     <tr>
      <th>NAME</th><th>NORAD</th><th>ALT KM</th><th>SPEED KM/S</th>
     </tr>
    </thead>
    <tbody id="satTable">
     <tr><td colspan="4">Loading...</td></tr>
    </tbody>
   </table>
  </div>
 </div>

 <div class="panel">
  <h2>🧠 DIGITAL NETWORK STATUS</h2>
  <div id="networkStatus" class="note">
   डिजिटल मिशन कंट्रोल तैयार हो रहा है।
  </div>
 </div>

 <div class="panel">
  <h2>📚 DATA SOURCE & SCIENCE</h2>
  <p class="note">
   Orbital elements: CelesTrak public GP data.
   Orbit propagation: SGP4 using satellite.js.
   Map tiles: OpenStreetMap contributors.
   Data is subject to source availability and orbital prediction accuracy.
  </p>
  <p class="note">
   CelesTrak data को जरूरत के अनुसार ही अपडेट किया जाता है।
   इस प्रोजेक्ट में अधिकतम हर दो घंटे में एक बार GP डेटा डाउनलोड करने का प्रयास होगा।
  </p>
  <p>
   <a style="color:#6ee6df" target="_blank"
      href="https://celestrak.org/">CelesTrak</a> |
   <a style="color:#6ee6df" target="_blank"
      href="https://github.com/shashwatak/satellite-js">Satellite.js</a>
  </p>
 </div>

</div>

<footer>
 SWARAJ GALAXY X • DIGITAL SPACE RESEARCH PROJECT
</footer>

<script src="https://unpkg.com/leaflet@1.9.4/dist/leaflet.js"></script>

<script type="module">
import * as satellite from
 "https://esm.sh/satellite.js@6.0.1";

const DATA_URL =
 "https://celestrak.org/NORAD/elements/gp.php?GROUP=stations&FORMAT=TLE";

const CACHE_KEY="swx_orbit_tle";
const UPDATE_KEY="swx_orbit_update";

let satellites=[];
let selected=null;
let markers={};

const map=L.map("map").setView([20,78],2);

L.tileLayer("https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png",{
 maxZoom:9,
 attribution:"© OpenStreetMap contributors"
}).addTo(map);

const $=id=>document.getElementById(id);

function setStatus(message){
 $("dataStatus").textContent=message;
}

function parseTLE(text){
 const lines=text.split(/\r?\n/).map(x=>x.trim()).filter(Boolean);
 const result=[];

 for(let i=0;i<lines.length;i++){
  if(lines[i].startsWith("1 ") &&
     lines[i+1]?.startsWith("2 ")){
   try{
    const l1=lines[i];
    const l2=lines[i+1];
    const name="NORAD "+l1.substring(2,7).trim();

    const satrec=satellite.twoline2satrec(l1,l2);

    if(satrec.error===0){
     result.push({
      name,
      norad:l1.substring(2,7).trim(),
      satrec,
      marker:null,
      position:null
     });
    }
   }catch(e){}
  }
 }
 return result;
}

async function loadData(){
 try{
  setStatus("CelesTrak से सार्वजनिक कक्षीय डेटा प्राप्त हो रहा है...");
  const last=Number(localStorage.getItem(UPDATE_KEY)||0);
  const cached=localStorage.getItem(CACHE_KEY);
  const now=Date.now();

  if(cached && now-last<7200000){
   satellites=parseTLE(cached);
   setStatus("सेव किया गया डेटा इस्तेमाल हो रहा है। अगला डेटा अपडेट निर्धारित समय पर होगा।");
  }else{
   const response=await fetch(DATA_URL,{
    cache:"no-store"
   });
   if(!response.ok)throw Error("HTTP "+response.status);

   const text=await response.text();
   if(!text.includes("1 ") || !text.includes("2 "))
    throw Error("डेटा प्रारूप सही नहीं है");

   satellites=parseTLE(text);
   if(!satellites.length)throw Error("कोई मान्य TLE नहीं मिला");

   localStorage.setItem(CACHE_KEY,text);
   localStorage.setItem(UPDATE_KEY,String(now));

   setStatus("नया सार्वजनिक TLE डेटा प्राप्त हुआ।");
  }

  $("connection").textContent="● DATA CONNECTED";
  $("total").textContent=satellites.length;
  $("engineStatus").textContent="READY";
  $("networkStatus").textContent=
   satellites.length+" वास्तविक सूचीबद्ध अंतरिक्ष वस्तुएँ SGP4 ट्रैकिंग के लिए तैयार हैं।";

  renderTable();
  updatePositions();
 }catch(error){
  $("connection").textContent="● DATA ERROR";
  $("engineStatus").textContent="ERROR";
  setStatus("डेटा उपलब्ध नहीं: "+error.message+
   ". इंटरनेट, CORS या डेटा सेवा की उपलब्धता जाँचें।");
  $("networkStatus").textContent=
   "लाइव स्रोत उपलब्ध नहीं हुआ। पहले से सेव डेटा उपलब्ध होने पर उसका उपयोग करें।";
  if(!satellites.length){
   const cached=localStorage.getItem(CACHE_KEY);
   if(cached){
    satellites=parseTLE(cached);
    $("total").textContent=satellites.length;
    renderTable();
    updatePositions();
   }
  }
 }
}

function getPosition(sat,now){
 const pv=satellite.propagate(sat.satrec,now);
 if(!pv.position || !pv.velocity)return null;

 const gmst=satellite.gstime(now);
 const geo=satellite.eciToGeodetic(pv.position,gmst);

 const lat=satellite.degreesLat(geo.latitude);
 const lon=satellite.degreesLong(geo.longitude);
 const alt=geo.height;

 const v=pv.velocity;
 const speed=Math.sqrt(v.x*v.x+v.y*v.y+v.z*v.z);

 if(!Number.isFinite(lat+lon+alt+speed))return null;

 return {lat,lon,alt,speed};
}

function updatePositions(){
 const now=new Date();

 satellites.forEach(sat=>{
  const p=getPosition(sat,now);
  sat.position=p;
  if(!p)return;

  if(!sat.marker){
   sat.marker=L.circleMarker([p.lat,p.lon],{
    radius:5,
    color:"#4be6d4",
    fillColor:"#4be6d4",
    fillOpacity:.85,
    weight:1
   }).addTo(map);

   sat.marker.on("click",()=>selectSatellite(sat));
  }else{
   sat.marker.setLatLng([p.lat,p.lon]);
  }

  sat.marker.bindTooltip(sat.name+" • NORAD "+sat.norad);
 });

 renderTable();

 if(selected){
  const current=satellites.find(s=>s.norad===selected.norad);
  if(current && current.position){
   selected=current;
   showDetails(current);
  }
 }
}

function selectSatellite(sat){
 selected=sat;
 showDetails(sat);
 if(sat.position){
  map.setView([sat.position.lat,sat.position.lon],4);
 }
}

function showDetails(sat){
 const p=sat.position;
 if(!p)return;

 $("altitude").textContent=p.alt.toFixed(1);
 $("speed").textContent=p.speed.toFixed(2);
 $("details").innerHTML=
  "<b>"+escapeHTML(sat.name)+"</b><br>"+
  "NORAD ID: "+escapeHTML(sat.norad)+"<br>"+
  "Latitude: "+p.lat.toFixed(4)+"°<br>"+
  "Longitude: "+p.lon.toFixed(4)+"°<br>"+
  "Altitude: "+p.alt.toFixed(2)+" km<br>"+
  "Orbital speed: "+p.speed.toFixed(3)+" km/s<br>"+
  "Calculation: SGP4<br>"+
  "Calculation time: "+new Date().toISOString();
}

function escapeHTML(s){
 return String(s).replace(/[&<>"']/g,c=>({
  "&":"&amp;","<":"&lt;",">":"&gt;",
  '"':"&quot;","'":"&#39;"
 }[c]));
}

function renderTable(list=satellites){
 const body=$("satTable");
 body.innerHTML="";

 list.slice(0,150).forEach(sat=>{
  const p=sat.position;
  const tr=document.createElement("tr");
  tr.innerHTML=
   "<td>"+escapeHTML(sat.name)+"</td>"+
   "<td>"+escapeHTML(sat.norad)+"</td>"+
   "<td>"+(p?p.alt.toFixed(1):"--")+"</td>"+
   "<td>"+(p?p.speed.toFixed(2):"--")+"</td>";
  tr.onclick=()=>selectSatellite(sat);
  body.appendChild(tr);
 });
}

window.filterSatellites=()=>{
 const q=$("search").value.toLowerCase().trim();
 const filtered=satellites.filter(s=>
  s.name.toLowerCase().includes(q)||s.norad.includes(q)
 );
 renderTable(filtered);
};

window.loadData=loadData;

loadData();

// Position calculation every second.
// Public orbital data download is NOT repeated every second.
setInterval(updatePositions,1000);

</script>
</body>
</html>
